/*
 * escape_display_name.c -- Escape a display name, hopefully per RFC 5322.
 *
 * This code is Copyright (c) 2012, by the authors of nmh.  See the
 * COPYRIGHT file in the root directory of the nmh distribution for
 * complete copyright information.
 */

#include <sys/types.h>
#include <h/utils.h>
#include <string.h>
#include <stdlib.h>

/* Escape a display name, hopefully per RFC 5322.  Assumes one-byte
   characters.  The char array pointed to by the name argument is
   modified in place.  Its size is specified by the namesize
   argument. */
void
escape_display_name (char *name, size_t namesize) {
    /* Quote and escape name that contains any specials, as necessary. */
    if (strpbrk("\"(),.:;<>@[\\]", name)) {
        char *destp, *srcp;
        /* Maximum space requirement would be if each character had
           to be escaped, plus enclosing double quotes, plus null termintor.
           E.g., 2 characters, "", would require 7, "\"\""0, where that 0
           is '\0'. */
        char *tmp = mh_xmalloc (2*strlen(name) + 3);

        for (destp = tmp, srcp = name; *srcp; ++srcp) {
            if (srcp == name) {
                /* Insert initial double quote, if needed. */
                if (*srcp != '"') {
                    *destp++ = '"';
                }
            } else {
                /* Escape embedded, unescaped double quote. */
                if (*srcp == '"' && *(srcp+1) != '\0' && *(srcp-1) != '\\') {
                    *destp++ = '\\';
                }
            }

            *destp++ = *srcp;

            /* End of name. */
            if (*(srcp+1) == '\0') {
                /* Insert final double quote, if needed. */
                if (*srcp != '"') {
                    *destp++ = '"';
                }

                *destp++ = '\0';
            }
        }

        if (strcmp (tmp, "\"")) {
            /* assert (strlen(tmp) + 1 == destp - tmp); */
            size_t len = destp - tmp;
            strncpy (name, tmp, len <= namesize  ?  len  :  namesize);
        } else {
            /* Handle just " as special case here instead of above. */
            strncpy (name, "\"\\\"\"", namesize);
        }

        name[namesize - 1] = '\0';

        free (tmp);
    }
}