/* This is simple demonstration of how to use expat. This program
   reads an XML document from standard input and writes a line with
   the name of each element to standard output indenting child
   elements by one tab stop more than their parent element.
*/

#include <stdio.h>
#include "DebugPrint.h"

#include "expat.h"

static void XMLCALL
startElement(void *userData, const char *name, const char **atts)
{
  int i;
  int *depthPtr = (int*)userData;
  for (i = 0; i < *depthPtr; i++)
    DebugPrint("\t");
  DebugPrint(name);
  *depthPtr += 1;
}

static void XMLCALL
endElement(void *userData, const char *name)
{
  int *depthPtr = (int*)userData;
  *depthPtr -= 1;
}

int
expatElement(void)
{
  char buf[BUFSIZ];
  static char * text[] =
  {
        "<hello field=\"field1\">\n" ,
        "   <howdy something=\"something2\"/>\n" ,
        "</hello>\n" ,
        ""
  } ;
  const int numLines = sizeof( text ) / sizeof( text[ 0 ] ) ;
  XML_Parser parser = XML_ParserCreate(NULL);
  int done;
  int depth = 0;
  int line = 0 ;

  DebugPrint( "expatElement:\n" );

  XML_SetUserData(parser, &depth);
  XML_SetElementHandler(parser, startElement, endElement);
  do {
    done = ( line == numLines - 1 ) ;
    int len  = strlen( text[ line ] ) ;
    memcpy( buf, text[ line ], len + 1 ) ;
    ++ line ;
    if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
      DebugPrint(
              "%s at line %d\n",
              XML_ErrorString(XML_GetErrorCode(parser)),
              XML_GetCurrentLineNumber(parser));
      return 1;
    }
  } while (!done);
  XML_ParserFree(parser);
  return 0;
}
