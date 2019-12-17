/* lfsr.c - Template Test of 64 bit LFSR  Version 0.1.0 */
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

#include "template.h"

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/* 64 bit LFSR is 64,63,61,60 with low order bit equal  */
/* to 64                                                */
/********************************************************/

/* This program runs a template test on a plain         */
/* 64 bit LFSR random number generator.                 */
/* The period length of the LFSR is longer than the     */
/* number of samples.                                   */
/* The expected result from this test is a P-value      */
/* of 1.0.                                              */

#define MYLFSROUT (xx->out = (((xx->lfsr >> 4) \
   ^ (xx->lfsr >> 3) \
   ^ (xx->lfsr >> 1) \
   ^ (xx->lfsr >> 0)) & 1))

#define MYLFSRLOWBIT (xx->lowbit = xx->major & 1)

#define MYLFSRROLL (xx->lfsr0 = xx->major = \
(xx->major >> 1) | (xx->out << 31))

#define MYLFSRCARRY (xx->lfsr = xx->minor = \
(xx->minor >> 1) | (xx->lowbit << 31))

#define MYLFSR (MYLFSROUT,MYLFSRLOWBIT,MYLFSRROLL,MYLFSRCARRY)

/* generate a uniform random number from 0 to 2^BITS */
unsigned int gen_token(xxfmt *xx)
   {
   unsigned int x;
   MYLFSR;
   xx->lfsr &= 0xffff;
   x = xx->lfsr & 7;
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
   qsetup(xx);    /* init queues and numeric fields */
   /* allocate GSL random number generator to set initial */
   /* values in the three fibonacci numbers               */
   xx->rng = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus);
   gsl_rng_set(xx->rng, xx->dttk);
   xx->lfsr  = xx->minor = gsl_rng_get(xx->rng);
   xx->lfsr0 = xx->major = gsl_rng_get(xx->rng);
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
