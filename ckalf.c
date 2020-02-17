/* ckalf.c - Validate alfabet  Version 0.1.0 */
/* Copyright (C) 2020 aquila57 at github.com */

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

/* validate the alfabet */

int ckalf(xxfmt *xx)
   {
   int len;
   int indx;
   char *p,*q;
   char cklst[256];
   xx->alflen = 0;
   len = strlen(xx->alf);
   if (len > 72) return(1);
   p = (char *) cklst;
   q = (char *) cklst + 256;
   while (p < q) *p++ = '\0';
   p = (char *) xx->alf;
   q = (char *) xx->alf + len;
   while (p < q)
      {
      char *r;
      if (*p < 0x21) return(1);
      if (*p > 0x7e) return(1);
      indx = (int) *p;
      r = (char *) cklst + indx;
      if (*r != 0) return(1);
      *r = 1;
      p++;
      } /* for each letter in alfabet */
   xx->alflen = len;
   return(0);
   } /* ckalf */
