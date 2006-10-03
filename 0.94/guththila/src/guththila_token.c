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
 */


#include "guththila_token.h"
#include "guththila_unicode.h"
/* #include "guththila_string.h" */
#include <axis2_string.h>


AXIS2_EXTERN guththila_token_t *
guththila_token_create_token_buffer(axis2_env_t *environment,
        int size)
{
    guththila_token_t *tok =
        (guththila_token_t *) AXIS2_MALLOC(environment->allocator,
                sizeof(guththila_token_t) * size);
    tok->size = size;
    return tok;
}


AXIS2_EXTERN void
guththila_token_free_token_buffer(axis2_env_t * environment,
        guththila_token_t * tok)
{
    if (tok)
        AXIS2_FREE(environment->allocator, tok);
}


AXIS2_EXTERN void
guththila_token_exception()
{
    printf("Throws new token Exception");
    /* Samisa : we should define the error code and error desctioption and return error code to user
       no use of using printf within a library
       please delete this comment once this is fixed.
     */
}


AXIS2_EXTERN int
guththila_token_length(axis2_env_t * environment,
        guththila_token_t * tok)
{
    if (tok->end)
        return (tok->end) - (tok->start) + 1;
    else
        guththila_token_exception();
    return 0;
}


AXIS2_EXTERN guththila_token_t *
guththila_token_grow(axis2_env_t * environment,
        guththila_token_t * tok)
{
    tok->size <<= 1;
    tok = (guththila_token_t *) AXIS2_REALLOC(environment->allocator,
            tok, sizeof(guththila_token_t) * tok->size);

    return tok;
}


AXIS2_EXTERN guththila_token_t *
guththila_token_append(axis2_env_t * environment,
        guththila_token_t * tok)
{
    if (++(tok->last) > (tok->size))
        guththila_token_grow(environment, tok);
    return &tok[tok->last];
}


AXIS2_EXTERN guththila_token_t *
guththila_token_last(axis2_env_t * environment,
        guththila_token_t * tok)
{
    if (tok->last < 0)
        guththila_token_exception();
    return &tok[tok->last];
}


AXIS2_EXTERN int
guththila_token_count(axis2_env_t * environment,
        guththila_token_t * tok)
{
    return tok->last;
}

AXIS2_EXTERN guththila_char_t *
guththila_token_char_ref(axis2_env_t * environment,
        guththila_char_t * buffer)
{
    int len;
    int ii;
    int ix;
    guththila_char_t *ref_buffer = NULL;

    len = AXIS2_STRLEN(buffer);
    ref_buffer = (guththila_char_t *) AXIS2_MALLOC(
                environment->allocator, len + 1);


    for (ii = 0, ix = 0; ii < len; ii++, ix++)
    {
        if (buffer[ii] == '&')
        {
            if (buffer[ii + 1] == 'a'
                    && buffer[ii + 2] == 'm'
                    && buffer[ii + 3] == 'p' && buffer[ii + 4] == ';')
            {
                ref_buffer[ix] = '&';
                ii += 4;
            }
            else if (buffer[ii + 1] == 'g'
                    && buffer[ii + 2] == 't' && buffer[ii + 3] == ';')
            {
                ref_buffer[ix] = '>';
                ii += 3;
            }
            else if (buffer[ii + 1] == 'l'
                    && buffer[ii + 2] == 't' && buffer[ii + 3] == ';')
            {
                ref_buffer[ix] = '<';
                ii += 3;
            }
            else if (buffer[ii + 1] == 'q'
                    && buffer[ii + 2] == 'u'
                    && buffer[ii + 3] == 'o'
                    && buffer[ii + 4] == 't' && buffer[ii + 5] == ';')
            {
                ref_buffer[ix] = '"';
                ii += 5;
            }
            else if (buffer[ii + 1] == 'a'
                    && buffer[ii + 2] == 'p'
                    && buffer[ii + 3] == 'o'
                    && buffer[ii + 4] == 's' && buffer[ii + 5] == ';')
            {
                ref_buffer[ix] = '\'';
                ii += 5;
            }
            else
                guththila_token_exception();
        }
        else
            ref_buffer[ix] = buffer[ii];
    }
    return ref_buffer;
}


AXIS2_EXTERN guththila_char_t *
guththila_token_to_string(axis2_env_t * environment,
        guththila_token_t * tok, int unicode)
{
    if (tok)
    {
        if (unicode == None)
        {
            int length;
            guththila_char_t *buffer = NULL;
            length = guththila_token_length(environment, tok);
            buffer = (guththila_char_t *) AXIS2_MALLOC(environment->allocator,
                    length + 1);
            memcpy(buffer, tok->start, length);
            buffer[length] = 0;
            if (tok->ref)
                return guththila_token_char_ref(environment, buffer);
            else
                return buffer;
        }
        else
        {
            int length;
            guththila_char_t *buffer = NULL;
            length = guththila_token_length(environment, tok);

            buffer = (guththila_char_t *) AXIS2_MALLOC(
                        environment->allocator, length + 1);

            memcpy(buffer, tok->start, length);
            buffer[length] = 0;
            return guththila_token_convert_utf16_to_utf8(environment, buffer,
                    length);
        }
    }
    else
        return NULL;
}


AXIS2_EXTERN void
guththila_token_relocate(axis2_env_t * environment,
        guththila_token_t * tok, int offset)
{
    tok->start -= offset;
    tok->end -= offset;
}


AXIS2_EXTERN int
guththila_token_compare(axis2_env_t * environment,
        guththila_token_t * tok, const guththila_char_t * s,
        int n, int unicode_state)
{
    if (unicode_state == None)
        return strncmp(tok->start, s, n);
    else
    {
        guththila_char_t *buffer = NULL;
        buffer = guththila_token_to_string(environment, tok, unicode_state);
        return strncmp(buffer, s, n);
    }
}


AXIS2_EXTERN int
guththila_token_length_utf16(axis2_env_t * environment,
        unsigned int utf16_ch)
{
    int length;

    if (0x80 > utf16_ch)
        length = 1;
    else if (0x800 > utf16_ch)
        length = 2;
    else if (0x10000 > utf16_ch)
        length = 3;
    else if (0x200000 > utf16_ch)
        length = 4;
    else if (0x4000000 > utf16_ch)
        length = 5;
    else
        length = 6;

    return length;
}


AXIS2_EXTERN guththila_char_t *
guththila_token_build_utf8(axis2_env_t * environment,
        unsigned int utf16_ch, int length)
{
    guththila_UTF8_char mask = 0;
    int ii = 0;
    guththila_char_t *buffer =
        (guththila_char_t *) AXIS2_MALLOC(environment->allocator,
                length + 1);
    memset(buffer, 0, length + 1);

    if (length == 1)
        buffer[0] = utf16_ch;
    else
    {
        switch (length)
        {
            case 1:
                break;
            case 2:
                mask = 0xc0;
                break;
            case 3:
                mask = 0xe0;
                break;
            case 4:
                mask = 0xf0;
                break;
            case 5:
                mask = 0xf8;
                break;
            case 6:
                mask = 0xfc;
                break;
        };

        for (ii = length - 1; ii > 0; ii--)
        {
            buffer[ii] = (utf16_ch & 0x3f) | 0x80;
            utf16_ch >>= 6;
        }

        buffer[0] = utf16_ch | mask;
        buffer[length] = 0;
    }
    return buffer;
}


AXIS2_EXTERN guththila_char_t *
guththila_token_convert_utf16_to_utf8(axis2_env_t * environment,
        guththila_char_t * buffer, int length)
{
    unsigned int utf16_char = 0;
    int length_utf16 = 0;
    int total_length = 0;
    guththila_char_t *input_buffer = buffer;
    guththila_char_t *output_char = 0;
    int ii = 0;
    guththila_char_t *output_buffer =
        (guththila_char_t *) AXIS2_MALLOC(environment->allocator, 1);
    memset(output_buffer, 0, 1);
    for (ii = 0; length > ii;)
    {
        utf16_char = *((guththila_UTF16_char *) & input_buffer[ii]);
        ii += 2;
        length_utf16 = guththila_token_length_utf16(environment, utf16_char);
        output_char =
            guththila_token_build_utf8(environment, utf16_char,
                    length_utf16);
        total_length += length_utf16;
        output_buffer = strcat(output_buffer, output_char);
    }
    return output_buffer;
}
