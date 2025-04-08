# genJsonEsp
generate c code from c binary to use in esp32 webservice

# problem description
If you program a webserver with esp32, then you need sometime to generate a json file out of varaibles of the esp32 internal memory. If you do that for one or two variables you can do it like:

    String str = "{\n";
    str += "\"myvar1\":\"" + String(myvar1) + "\";\n";
    str += "}"

if you still uses a struct, than this method get anoing and much more difficult. So I decided to write a code generator in python to generate that code for me.


# how it works
The is a python interface in the gdp ( the gnu debugger ) , there you can look into given ELF files and extract and describe structs.
The description of that interface can be found in "https://sourceware.org/gdb/current/onlinedocs/gdb.html/Types-In-Python.html"

# files that needed
* run_generator: (modify it to your needs) the shell script, that calls the ddb with your binary
* genJson.txt: (modify it) type in this file the type name(s) of your struct for code generation
* genJson.py: (no need to modify) this script write the c.Files for you
* struct2json.py: (no need to modify) this file do the work
* genJson.ino: this is the output file of the generator with the code, you can import into your (Arduino) project

# instruction manuel
* first have a Arduino project, that have no compilation errors
* put all your variables needed in one struct
* call in the Arduino gui: Arduino->Sketch->export compiled binary
* modify the generator files to your need
* copy the resulting .ino file in you project.

# example
I copied an easy project example in the directory "genJsonEsp"
the files:
* genJsonEsp.ino
* webserver.ino
* wlan_credicals.h
includes the original project.
The File "z_genJson.ino" have the generated code. One hint, the File should be the last file (name = "z_*.ino") in your project, so that the struct is known.

