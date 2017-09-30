/*****************************************************************
 * outline.c
 *
 * Copyright 1999, Clark Cooper
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the license contained in the
 * COPYING file that comes with the expat distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Read an XML document from a buffer and print an element
 * outline on standard output.
 */


#include <stdio.h>
#include <string.h>
#include "DebugPrint.h"
#include "expat.h"

#define BUFFSIZE        8192

static char Buff[BUFFSIZE];

static int Depth;

static void XMLCALL
start(void *data, const char *el, const char **attr)
{
  int i;

  for (i = 0; i < Depth; i++)
    DebugPrint("  ");

  DebugPrint("%s", el);

  for (i = 0; attr[i]; i += 2) {
    DebugPrint(" %s='%s'", attr[i], attr[i + 1]);
  }

  DebugPrint("\n");
  Depth++;
}

static void XMLCALL
end(void *data, const char *el)
{
  Depth--;
}

int
expatOutline(void)
{
  XML_Parser p = XML_ParserCreate(NULL);

  static char * text[] =
  {
        "<hello field=\"field1\">\n" ,
        "   <howdy something=\"something2\"/>\n" ,
        "</hello>\n" ,
        ""
  } ;
  const int numLines = sizeof( text ) / sizeof( text[ 0 ] ) ;

  DebugPrint( "expatOutline:\n" );

  if (! p) {
    DebugPrint("Couldn't allocate memory for parser\n");
    return -1 ;
  }

  XML_SetElementHandler(p, start, end);

  for (int line = 0 ; line < numLines ; ++ line ) {
    int done = ( line == numLines - 1 ) ;
    int len  = strlen( text[ line ] ) ;
    memcpy( Buff, text[ line ], len + 1 ) ;

    if (XML_Parse(p, Buff, len, done) == XML_STATUS_ERROR) {
      DebugPrint("Parse error at line %d:\n%s\n",
              XML_GetCurrentLineNumber(p),
              XML_ErrorString(XML_GetErrorCode(p)));
      return -3 ;
    }

    if (done)
      break;
  }
  return 0;
}
