/* fibotmplt.c - Fibonacci Template Test Program  Version 0.1.0 */
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

/* This program runs a template test on a fibonacci random           */
/* number generator.                                                 */
/* The expected result from this test is a P-value of 1.0            */

#include "template.h"

/* generate a uniform random number from 0 to 2^BITS */
unsigned int gen_token(xxfmt *xx)
   {
   unsigned int x;
   xx->fibonum1 = xx->fibonum2;
   xx->fibonum2 = xx->fibonum3;
   xx->fibonum3 = xx->fibonum1 + xx->fibonum2;
   x = xx->fibonum3 >> (32-BITS);
   xx->count++;
   return(x);
   } /* gen_token */

/* build a random template queue */
/* if BITS is equal to 3, each token is a binary */
/* number from zero to 7 */
void bldtmplt(xxfmt *xx)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = gen_token(xx);
      pushq(xx->tmplthead, x);
      } /* for each element in template FIFO queue */
   } /* bldtmplt */

/* Create the initial sample queue the same size as */
/* the template */
/* the tokens in this sample queue should not match */
/* the template queue.  */
void bldlst(xxfmt *xx)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = gen_token(xx);
      pushq(xx->lsthead, x);
      } /* for each element in active list FIFO queue */
   } /* bldlst */

/* update the sample FIFO queue with a new sample */
/* compare the sample queue to the template queue */
/* to see if a wrap-around error has occurred */
/* update the tally array based on the number of */
/* sample tokens that match the template */

void sample(xxfmt *xx)
   {
   unsigned int newnum;
   popq(xx->lsttail);
   newnum = gen_token(xx);
   pushq(xx->lsthead, newnum);
   tally(xx);
   } /* sample */

int main(void)
   {
   int i;                      /* sample loop counter */
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /****************************************************/
   /* initialize queues and numeric fields             */
   /* initialize the random number generator           */
   /****************************************************/
   qsetup(xx);
   /* allocate GSL random number generator to set initial */
   /* values in the three fibonacci numbers               */
   xx->rng = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus);
   gsl_rng_set(xx->rng, xx->dttk);
   xx->fibonum1 = gsl_rng_get(xx->rng);
   xx->fibonum2 = gsl_rng_get(xx->rng);
   xx->fibonum3 = gsl_rng_get(xx->rng);
   gsl_rng_free(xx->rng);
   /****************************************************/
   bldtmplt(xx);   /* build template queue */
   bldlst(xx);     /* build sample queue   */
   i = SMPLS;
   while(i--)
      {
      /* take one sample                               */
      /* compare sample queue to template queue        */
      sample(xx);     /* take one sample */
      } /* for each sample */
   calcchi(xx);    /* run chi square test on tallies */
   freeall(xx);    /* free all allocated memory */
   return(0);
   } /* main */
