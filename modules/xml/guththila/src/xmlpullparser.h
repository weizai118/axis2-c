/*
 *   Copyright 2004,2005 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *	
 * @author Dinesh Premalal (xydinesh@gmail.com, premalwd@cse.mrt.ac.lk)	
 */

#ifndef __XML_PULLPARSER__INCLUDED__
#define __XML_PULLPARSER__INCLUDED__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "buffer.h"
#include "reader.h"
#include "token.h"
#include "namespace.h"
#include "depth.h"
#include "stack.h"
#include "unicode.h"

#ifndef XMLPARSERAPI
#define XMLPARSERAPI		/* as nothing */
#endif

#ifndef PRIVATE
#define PRIVATE 		/* as nothing */
#endif

#define p_FILE __FILE__		/* file name */
#define LINE __LINE__		/* line number */

typedef void *XML_PULLPARSER;

enum status
  {
    S_0 = 0,
    S_1,
    S_2,
    S_3,
    S_4
  };

enum event_types 
  {
    START_DOCUMENT = 10, 
    START_ELEMENT = 20, 
    END_ELEMENT = 30, 
    EMPTY_ELEMENT = 40, 
    CHARACTER = 50, 
    ENTITY_REFERANCE = 60, 
    COMMENT = 70
  };
enum event_types EVENT;


typedef struct xmlpullpaser
{
  BUFFER *buffer;
  READER *reader;
  TOKEN *prefix;
  TOKEN *name;
  TOKEN *value;
  STACK *stack;
  STACK *attrib;
  STACK *namesp;
  STACK *dep;
  int _next;
  int offset;
  int last;
  int unicode_state;
  enum status STATUS;
}XML_PullParser;


PRIVATE int XML_PullParser_read (XML_PullParser *p);
PRIVATE int XML_PullParser_nextChar (XML_PullParser *p, int eof);
PRIVATE int XML_PullParser_tokenize (XML_PullParser *p);
PRIVATE int XML_PullParser_Exception (char *s, int line);
PRIVATE int XML_PullParser_skipS (XML_PullParser *p, int c);
PRIVATE int XML_PullParser_processXmlDecl (XML_PullParser *p);
PRIVATE int XML_PullParser_processVersionInfo (XML_PullParser *p);
PRIVATE int XML_PullParser_processEncodingDecl (XML_PullParser *p);
PRIVATE int XML_PullParser_processSDDecl (XML_PullParser *p);
PRIVATE void XML_PullParser_openToken (XML_PullParser *p);
PRIVATE void XML_PullParser_closeToken (XML_PullParser *p, int t, int refer);
PRIVATE char* XML_PullParser_lastChar (XML_PullParser *p);
PRIVATE int XML_PullParser_processEq (XML_PullParser *p, int c);
PRIVATE void XML_PullParser_addAttribute (XML_PullParser *p, TOKEN *name, TOKEN *value);
PRIVATE void XML_PullParser_addAttribute_with_prefix (XML_PullParser *p, TOKEN *prefix, TOKEN *name, TOKEN *value);
PRIVATE int XML_PullParser_processCharData (XML_PullParser *p);
PRIVATE int XML_PullParser_processSTagOrEmtyElem (XML_PullParser *p);
PRIVATE int XML_PullParser_processComment (XML_PullParser *p);
PRIVATE int XML_PullParser_processPI (XML_PullParser *p);
PRIVATE int XML_PullParser_processETag (XML_PullParser *p);
PRIVATE void XML_PullParser_reset (XML_PullParser *p);
PRIVATE int XML_PullParser_processName (XML_PullParser *p);
PRIVATE int XML_PullParser_processAttribute (XML_PullParser *p, int c);
PRIVATE int XML_PullParser_processAttValue (XML_PullParser *p, int c);
PRIVATE int XML_PullParser_isS (int c);
PRIVATE void XML_PullParser_relocateTokens (XML_PullParser *p, int offset);
PRIVATE void XML_PullParser_shift (XML_PullParser *p);
PRIVATE void XML_PullParser_addNamespace (XML_PullParser *p, TOKEN *name, TOKEN *uri);
PRIVATE void XML_PullParser_openElement (XML_PullParser *p);
PRIVATE void XML_PullParser_closeElement (XML_PullParser *p);
PRIVATE int XML_PullParser_from_utf16 (XML_PullParser *p, int eof);
PRIVATE int XML_PullParser_is_valid_starting_char (XML_PullParser *p, int c);

int XMLPARSERAPI XML_PullParser_next (XML_PullParser *p);
XML_PULLPARSER XMLPARSERAPI XML_PullParser_createPullParser (READER *r);
void XMLPARSERAPI XML_PullParser_freePullParser ();
int XMLPARSERAPI XML_PullParser_getAttributeCount (XML_PullParser *p);
char *XMLPARSERAPI XML_PullParser_getAttributeName (XML_PullParser *p, ATTRIBUTE *att);
char *XMLPARSERAPI XML_PullParser_getAttributeValue (XML_PullParser *p, ATTRIBUTE *att);
char *XMLPARSERAPI XML_PullParser_getAttributePrefix (XML_PullParser *p, ATTRIBUTE *att);
ATTRIBUTE *XMLPARSERAPI XML_PullParser_getAttribute (XML_PullParser *p);
char *XMLPARSERAPI XML_PullParser_getAttributeName_by_number (XML_PullParser *p, int i);
char *XMLPARSERAPI XML_PullParser_getAttributeValue_by_number (XML_PullParser *p, int i);
char *XMLPARSERAPI XML_PullParser_getAttributePrefix_by_number (XML_PullParser *p, int i);
char *XMLPARSERAPI XML_PullParser_getName (XML_PullParser *p);
char *XMLPARSERAPI XML_PullParser_getPrefix (XML_PullParser *p);
char *XMLPARSERAPI XML_PullParser_getValue (XML_PullParser *p);
NAMESPACE *XMLPARSERAPI XML_PullParser_getNamespace (XML_PullParser *p);
int XMLPARSERAPI XML_PullParser_getNamespaceCount (XML_PullParser *p);
char *XMLPARSERAPI XML_PullParser_getNamespaceUri (XML_PullParser *p, NAMESPACE *ns);
char *XMLPARSERAPI XML_PullParser_getNamespacePrefix (XML_PullParser *p, NAMESPACE *ns);
char *XMLPARSERAPI XML_PullParser_getNamespacePrefix_by_number (XML_PullParser *p, int i);
char *XMLPARSERAPI XML_PullParser_getNamespaceUri_by_number (XML_PullParser *p, int i);

#endif 
