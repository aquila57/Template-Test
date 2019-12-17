/* gsltmplt.c - GSL Template Test Program  Version 0.1.0 */
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

/* This program uses the GNU Scientific Library to generate          */
/* random samples,                                                   */
/* and to calculate P-value and chi square range.                    */

/* This program depends on environment variables being set.          */
/* Test this program with the gsltmplt.sh script.                    */

/* This program runs the template test on uniform random             */
/* data.                                                             */
/* The wrap-around error should not occur in this test.              */
/* The P-value in the chi square test should pass                    */
/* the Kolmogorov-Smirnov test.                                      */
/* However, the GSL randu generator does fail this test              */
/* with a P-value of 1.0.                                            */
/* The GSL slatec generator fails this test with wrap-around error.  */

#include "template.h"

/* generate a uniform random number from 0 to 2^BITS */
unsigned int gen_num(xxfmt *xx)
   {
   unsigned int x;
   double num;
   num = gsl_rng_uniform(xx->rng) * xx->dbllmt;
   x = (unsigned int) floor(num);
   xx->count++;
   return(x);
   } /* gen_num */

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
      x = (unsigned int) gen_num(xx);
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
      x = gen_num(xx);
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
   newnum = gen_num(xx);
   pushq(xx->lsthead, newnum);
   tally(xx);
   } /* sample */

int main(void)
   {
   int i;
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
   qsetup(xx);   /* initialize queues */
   gsl_rng_env_setup();
   xx->typ = (gsl_rng_type *) gsl_rng_default;
   xx->rng = (gsl_rng *) gsl_rng_alloc(xx->typ);
   /* allocate GSL random number generator to set initial */
   /* values in the three fibonacci numbers               */
   gsl_rng_set(xx->rng, xx->dttk);
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
   gsl_rng_free(xx->rng);
   freeall(xx);    /* free all allocated memory */
   return(0);
   } /* main */
