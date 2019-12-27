/* diepfx.c - Bypass Dieharder prefix  Version 0.1.0 */
/* Copyright (C) 2019 aquila57 at github.com */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

#include "template.h"
#include <errno.h>

/* Bypass Dieharder prefix                            */
/* The Dieharder command to produce random output is: */
/* dieharder -g nnn -t sss -o                         */
/* where nnn is the number of the Dieharder random    */
/* number generator and                               */
/* sss is the number of 32-bit words to generate      */
/* The output from Dieharder is in ASCII format.      */
/* Dieharder writes one line per 32-bit generation    */
/* of output.                                         */
/* The prefix ends with numbit: 32                    */

void diepfx(xxfmt *xx)
   {
   int len;
   char buf[256];
   while (1)
      {
      int rslt;
      len = scanf("%s", buf);
      if (len < 1)
         {
         if (feof(stdin))
	    {
	    fprintf(stderr,"diepfx: end of "
	       "file, len %d\n", len);
	    exit(1);
	    } /* if end of file */
         if (ferror(stdin))
            {
            perror("diepfx: read error\n");
            exit(1);
            } /* read error */
         fprintf(stderr,"diepfx: blank line\n");
         exit(1);
         } /* if eof or read error */
      if (len > 1)
         {
         fprintf(stderr,"diepfx: read error\n");
         fprintf(stderr,"scanf read more than "
            "one token %d\n", len);
         exit(1);
         } /* invalid input */
      rslt = strcmp(buf,"numbit:");
      if (!rslt) break;
      } /* for each token in prefix */
   /* bypass the 32 in "numbit: 32" */
   len = scanf("%s", buf);
   if (len < 1)
      {
      if (feof(stdin))
	 {
	 fprintf(stderr,"diepfx: end of file "
	    "readint 32, len %d\n", len);
	 exit(1);
	 } /* if end of file */
      if (ferror(stdin))
         {
         perror("diepfx: read error\n");
         exit(1);
         } /* read error */
      fprintf(stderr,"diepfx: blank line\n");
      exit(1);
      } /* if eof or read error */
   if (len > 1)
      {
      fprintf(stderr,"diepfx: read error\n");
      fprintf(stderr,"scanf read more than "
         "one token %d\n", len);
      exit(1);
      } /* invalid input */
   } /* diepfx */
