# LICENSE : http://www.apache.org/licenses/LICENSE-2.0 
# (c) 2025 frankb 
#
# more info for gdb usage:
# https://sourceware.org/gdb/current/onlinedocs/gdb.html/Types-In-Python.html

import math
import gdb
import os.path
import sys
from datetime import datetime

def genTxtForStruct ( struct , varPrefix , intend) :
    print( intend + "genTxtForStruct")

    komma = " "
    s = intend + '{/* start genTxtForStruct (%i) */\n' % len(intend)
    #s += intend + 'str += " %s\\"gen_version\\":\\"%s\\"\\n\";\n' %  ( intend , datetime.today().isoformat() )
    for field in struct.fields():
        print( intend + "+proceed with structfield: %s.%s , type='%s'" % ( varPrefix , field.name ,  field.type ) )
        s += intend + 'str += "%s%s\\"%s\\":"; ' % (intend,komma,field.name)
        s += genTxtFromType( field.type , field.name , varPrefix , intend + "  " )
        s += 'str += "\\n";\n'
        komma = ","
    s += intend + '}/* end genTxtForStruct (%i) */\n' % len(intend)
    return s

def getTxtForArray( type , name , varPrefix , intend ):

    print( intend + "getTxtForArray")
    
    s = intend + '{/* start getTxtForArray (%i) */\n' % len(intend)
    s += '%sstr += "[";\n' % ( intend )

    # varname for index, the index needs unique.
    k = "k" + str( len(intend) )
    
    s += intend + 'for( int %s=0 ; %s<%i ; %s++ ) {\n' % ( k,k, type.range()[1]+1 ,k) 
    s += intend + '  if (%s) str += ",";\n' % k

    s += intend + '  ' 
    s += genTxtFromType( type.target() , "" , varPrefix + name + "[%s]" % k, intend + "  " )
    
    s += "\n" + intend + '};\n'
    s += intend + 'str += "]";\n'

    s += intend + '}/* end getTxtForArray (%i) */\n' % len(intend)
    s += intend
    return s 

def genTxtFromType( type , name , varPrefix , intend ):

    # welcher basictype ist das?
    basictype = gdb.types.get_basic_type(type)
    code = (gdb.types.get_basic_type(type)).code

    print( intend + "genTxtFromType: entry=%s type=%s basictype=%s" % ( name , type.name  , basictype ) )
    
    if type.name == "char":
        return 'str += String( (uint8_t) %s%s ); ' % (varPrefix,name)
    if code == gdb.TYPE_CODE_INT or code == gdb.TYPE_CODE_FLT:
        return 'str += String(%s%s);' % (varPrefix,name)
    if code == gdb.TYPE_CODE_BOOL:
        return 'str += String(%s%s*1); ' % (varPrefix,name)
    # Achtung: String ist ein pointer, deshalb fragen wir hier den Tynamen ab!
    if type.name == "String":
        return 'str += "\\"" + %s%s + "\\""; ' % (varPrefix,name)    
    if code == gdb.TYPE_CODE_ARRAY:
        return '\n' + getTxtForArray( type , name , varPrefix , intend + "" )

    if code == gdb.TYPE_CODE_STRUCT:
        # mist: struct in struct!
        str =  'str += "{\\n";\n'
        str += genTxtForStruct( type , varPrefix + name + "." , intend + "  " )
        str += intend + 'str += "%s}"; ' % intend
        return str
    
    return "#58 failure: for entry %s , type '%s' with code %i not found\n" % (field.name, field.type.name, code)

def struct2json ( struct ):

    print( "struct2json: structname: %s" % struct.name )
    
    # den Funktionskopf
    str  = "\r\n\r\n" 
    str += "/*! \\brief generate json for %s*/\n" % struct.name
    str += "String %s_json( struct %s * s1 ) {\n" % (struct.name,struct.name)

    # Einrueckung
    intend = "  "

    # es geht los: definition des Ausgabestring 
    str += intend + "String str = \"{\\n\";\n"

    # variable prefix eg. name of the struct
    varPrefix = "s1->"
 
    # struct generieren
    str += genTxtForStruct( struct , varPrefix , intend + "  " )

    # Version dazubauen
    intend = "    "
    str += intend + 'str += "%s,\\"gen_version\\":\\"%s\\"\\n\";\n' %  ( intend , datetime.today().isoformat() )
    
    # Abschluss des Json
    str += intend + "str += \"}\\n\";\n"
    
    # abschluss des Files    
    str += "  return str;\n"
    str += "}"

    return str
