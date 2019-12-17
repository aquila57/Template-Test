/* shwactual.c - Display actual tally array  Version 0.1.0 */
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

/* debugging routine to display the actual tally array */

void shwactual(xxfmt *xx)
   {
   int i;
   int indx;
   indx = 0;
   i = TMPLTSZ;
   while (i--)
      {
      if (xx->actual[indx] > 0.0)
         printf("indx %5d tally %.0f\n",
	    indx, xx->actual[indx]);
      indx++;
      } /* for each tally in actual > 10 */
   } /* shwactual */
