/* tally.c - Compare sample queue to template queue  Version 0.1.0 */
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

/* This program runs a template test on a 16 bit LFSR.               */
/* The expected result is a wrap-around error.                       */
/* The number of samples is larger than the period length            */
/* of the 16 bit LFSR.                                               */

#include "template.h"

/* Starting with the tail of each queue, */
/* compare the sample queue against the template queue */
/* The number of token matches is the index into the */
/* actual tally array. */
/* If the number of token matches is equal to TMPLTSZ */
/* a wrap-around error occurs, and the template test */
/* fails. */

void tally(xxfmt *xx)
   {
   int indx;
   qfmt *tmplt;
   qfmt *lst;
   indx = 0;
   tmplt = xx->tmplttail->next;
   lst   = xx->lsttail->next;
   while (tmplt != xx->tmplthead)
      {
      if (tmplt->num == lst->num)
         {
	 indx++;
         tmplt = tmplt->next;
	 lst   = lst->next;
	 } /* if match node */
      else break;
      } /* for each node in the template */
   xx->actual[indx] += 1.0;
   if (tmplt == xx->tmplthead)
      {
      fprintf(stderr,"tally: wrap around\n");
      fprintf(stderr,"index %d  token count %d\n",
         indx, xx->count);
      exit(1);
      } /* wrap around */
   } /* tally */
