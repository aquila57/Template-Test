/* qsetup.c - Initialize Queue Head and Tail     Version 0.1.0 */
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

/* This program allocates memory for queue head and tail nodes     */

void qsetup(xxfmt *xx)
   {
   double *p,*q;
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   /***********************************************/
   /* initialize queue head and tail              */
   /***********************************************/
   xx->tmplthead = (qfmt *) qinit();
   xx->tmplttail = (qfmt *) qinit();
   xx->lsthead   = (qfmt *) qinit();
   xx->lsttail   = (qfmt *) qinit();
   xx->tmplttail->next = xx->tmplthead;
   xx->tmplthead->prev = xx->tmplttail;
   xx->lsttail->next   = xx->lsthead;
   xx->lsthead->prev   = xx->lsttail;
   /***********************************************/
   /* initialize numeric fields                   */
   /* other than randomizing seeds                */
   /***********************************************/
   xx->count = xx->eofsw = xx->lowbit = xx->out = 0; 
   xx->chisq = xx->pvalue = 0.0;
   xx->onepi  = M_PI;
   xx->dbllmt = (1 << BITS);
   xx->maxint = MAXINT;
   p = (double *) xx->actual;
   q = (double *) xx->actual + TMPLTSZ;
   while (p < q) *p++ = 0.0;
   p = (double *) xx->maxint_tbl;
   q = (double *) xx->maxint_tbl + 2048;
   while (p < q) *p++ = 0.0;
   /****************************************************/
   /* initialize the random number generator           */
   /* time, date, and tick fields                      */
   /****************************************************/
   /* get clock ticks since boot                       */
   clk = times(&t);
   /* get date & time                                  */
   time(&now);
   /* combine date, time, and ticks into a single UINT */
   xx->dttk = (unsigned int) (now ^ clk);
   } /* qsetup */
