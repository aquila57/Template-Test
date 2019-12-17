/* dietmplt.c - Dieharder RNG Template Test  Version 0.1.0 */
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

/* This program depends on input data from dieharder.                */
/* Test this program with the dietmplt.sh script.                    */

/* This program runs the template test on uniform random             */
/* data.                                                             */
/* The wrap-around error should not occur in this test.              */
/* The P-value in the chi square test should pass                    */
/* the Kolmogorov-Smirnov test.                                      */
/* ????????????????????????????????????????????????????????????????? */
/* However, the GSL randu generator does fail this test              */
/* with a P-value of 1.0.                                            */
/* The GSL slatec generator fails this test with wrap-around error.  */
/* ????????????????????????????????????????????????????????????????? */

#include "template.h"

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s Dieharder_RNG_number\n", pgm);
   fprintf(stderr,"Example: %s 208\n", pgm);
   fprintf(stderr,"Where 208 is the kiss generator\n");
   fprintf(stderr,"Example: %s 053\n", pgm);
   fprintf(stderr,"Where 053 is the taus2 generator\n");
   exit(1);
   } /* putstx */

/* generate a uniform random number from 0 to 2^BITS */
unsigned int gen_num(xxfmt *xx)
   {
   unsigned int x;
   x = (unsigned int) getdie(xx);
   if (x == EOF)
      {
      fprintf(stderr,"gen_num: end of file\n");
      xx->eofsw = 1;
      } /* end of file condition */
   else
      {
      xx->count++;
      } /* else not eof */
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
      if (x == EOF || xx->eofsw)
         {
	 fprintf(stderr,"bldtmplt: end of file\n");
	 exit(1);
	 } /* end of file */
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
      if (x == EOF || xx->eofsw)
         {
	 fprintf(stderr,"bldlst: end of file\n");
	 exit(1);
	 } /* end of file */
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
   if (newnum == EOF || xx->eofsw)
      {
      fprintf(stderr,"sample: end of file\n");
      return;
      } /* end of file */
   pushq(xx->lsthead, newnum);
   tally(xx);
   } /* sample */

int main(int argc, char **argv)
   {
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /* initialize queues and numeric fields             */
   qsetup(xx);
   if (argc != 2) putstx(*argv);
   xx->generator = atoi(*(argv+1));
   if (xx->generator < 0 || xx->generator > 405)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   bld_maxint(xx);
   if (xx->maxint_tbl[xx->generator] == 0)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   xx->maxint = xx->maxint_tbl[xx->generator];
   /****************************************************/
   /* initialize the random number generator           */
   /****************************************************/
   gsl_rng_env_setup();
   xx->typ = (gsl_rng_type *) gsl_rng_default;
   xx->rng = (gsl_rng *) gsl_rng_alloc(xx->typ);
   /* allocate GSL random number generator to set initial */
   /* values in the three fibonacci numbers               */
   gsl_rng_set(xx->rng, xx->dttk);
   /****************************************************/
   bldtmplt(xx);   /* build template queue */
   if (!xx->eofsw) bldlst(xx);   /* build sample queue */
   while(!xx->eofsw)
      {
      /* take one sample                               */
      /* compare sample queue to template queue        */
      sample(xx);     /* take one sample */
      } /* for each sample */
   calcchi(xx);    /* run chi square test on tallies */
   gsl_rng_free(xx->rng);
   freeall(xx);
   return(0);
   } /* main */
