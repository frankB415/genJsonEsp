/* This Files were generated by "genJson.ino" 
 * LICENSE : http://www.apache.org/licenses/LICENSE-2.0
 * (c) 2025 frankb  * 2025-04-06T21:06:05.833748  */


/*! \brief generate json for myStruct1_t*/
String myStruct1_t_json( struct myStruct1_t * s1 ) {
  String str = "{\n";
    {/* start genTxtForStruct (4) */
    str += "     \"ip\":"; str += "\"" + s1->ip + "\""; str += "\n";
    str += "    ,\"millis\":"; str += String(s1->millis);str += "\n";
    str += "    ,\"i1\":"; str += String(s1->i1);str += "\n";
    str += "    ,\"nestedStruct\":"; str += "{\n";
        {/* start genTxtForStruct (8) */
        str += "         \"s2\":"; str += "\"" + s1->nestedStruct.s2 + "\""; str += "\n";
        str += "        ,\"i2\":"; str += String(s1->nestedStruct.i2);str += "\n";
        }/* end genTxtForStruct (8) */
      str += "      }"; str += "\n";
    str += "    ,\"arr1\":"; 
      {/* start getTxtForArray (6) */
      str += "[";
      for( int k6=0 ; k6<3 ; k6++ ) {
        if (k6) str += ",";
        
        {/* start getTxtForArray (8) */
        str += "[";
        for( int k8=0 ; k8<2 ; k8++ ) {
          if (k8) str += ",";
          str += String(s1->arr1[k6][k8]);
        };
        str += "]";
        }/* end getTxtForArray (8) */
        
      };
      str += "]";
      }/* end getTxtForArray (6) */
      str += "\n";
    str += "    ,\"nestedStruct2\":"; 
      {/* start getTxtForArray (6) */
      str += "[";
      for( int k6=0 ; k6<2 ; k6++ ) {
        if (k6) str += ",";
        str += "{\n";
          {/* start genTxtForStruct (10) */
          str += "           \"i3\":"; str += String(s1->nestedStruct2[k6].i3);str += "\n";
          str += "          ,\"b1\":"; str += String(s1->nestedStruct2[k6].b1*1); str += "\n";
          str += "          ,\"s3\":"; str += "\"" + s1->nestedStruct2[k6].s3 + "\""; str += "\n";
          }/* end genTxtForStruct (10) */
        str += "        }"; 
      };
      str += "]";
      }/* end getTxtForArray (6) */
      str += "\n";
    }/* end genTxtForStruct (4) */
    str += "    ,\"gen_version\":\"2025-04-06T21:06:05.824491\"\n";
    str += "}\n";
  return str;
}