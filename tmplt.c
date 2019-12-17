/* tmplt.c - Template Test Program  Version 0.1.0 */
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

/* This program uses the GNU Scientific Library to calculate         */
/* P-value and chi square range.                                     */

/* This program runs the template test on uniform random             */
/* data.                                                             */
/* The period length of the eegl random number generator             */
/* approximates 1.2 * 10^61036 generations.                          */
/* The wrap-around error should not occur in this test.              */
/* The P-value in the chi square test should pass                    */
/* the Kolmogorov-Smirnov test.                                      */

#include "template.h"
#include "eegl.h"

/* generate a uniform random number from 0 to 2^BITS */
unsigned int gen_token(xxfmt *xx, eefmt *ee)
   {
   unsigned int x;
   x = eeglpwr(ee,BITS);
   xx->count++;
   return(x);
   } /* gen_token */

/* build a random template queue */
/* if BITS is equal to 3, each token is a binary */
/* number from zero to 7 */
void bldtmplt(xxfmt *xx, eefmt *ee)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = gen_token(xx,ee);
      pushq(xx->tmplthead, x);
      } /* for each element in template FIFO queue */
   } /* bldtmplt */

/* Create the initial sample queue the same size as */
/* the template */
/* the tokens in this sample queue should not match */
/* the template queue.  */
void bldlst(xxfmt *xx, eefmt *ee)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = gen_token(xx,ee);
      pushq(xx->lsthead, x);
      } /* for each element in active list FIFO queue */
   } /* bldlst */

/* update the sample FIFO queue with a new sample */
/* compare the sample queue to the template queue */
/* to see if a wrap-around error has occurred */
/* update the tally array based on the number of */
/* sample tokens that match the template */

void sample(xxfmt *xx, eefmt *ee)
   {
   unsigned int newnum;
   popq(xx->lsttail);
   newnum = gen_token(xx,ee);
   pushq(xx->lsthead, newnum);
   tally(xx);
   } /* sample */

int main(void)
   {
   int i;
   xxfmt *xx;
   eefmt *ee;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   ee = (eefmt *) eeglinit();
   /* initialize queues and numeric fields             */
   qsetup(xx);    /* init queues and numeric fields */
   bldtmplt(xx,ee);   /* build template queue */
   bldlst(xx,ee);     /* build sample queue   */
   i = SMPLS;
   while(i--)
      {
      /* take one sample                               */
      /* compare sample queue to template queue        */
      sample(xx,ee);     /* take one sample */
      } /* for each sample */
   calcchi(xx);    /* run chi square test on tallies */
   free(ee->state);
   free(ee);
   freeall(xx);    /* free all allocated memory */
   return(0);
   } /* main */
