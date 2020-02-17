/* alftmplt.c - alfabet Template Test  Version 0.1.0 */
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

/* This program uses the GNU Scientific Library to calculate         */
/* P-value and chi square range.                                     */

/* This program runs the template test on uniform random             */
/* data. An alphabet of any number of letters is entered             */
/* as a parameter.  The program generates the template based         */
/* on etaus choosing which letters of the alphabet to form           */
/* the template.                                                     */
/* The period length of the etaus random number generator            */
/* approximates 1.2 * 10^61036 generations.                          */
/* The wrap-around error should not occur in this test.              */
/* The P-value in the chi square test should pass                    */
/* the Kolmogorov-Smirnov test.                                      */

#include "template.h"
#include "etaus.h"

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s alfabet\n", pgm);
   fprintf(stderr,"Example: %s ab\n", pgm);
   fprintf(stderr,"Example: %s \"ab\"\n", pgm);
   fprintf(stderr,"Alfabet rules:\n");
   fprintf(stderr,"Every letter is unique\n");
   fprintf(stderr,"Special ASCII characters allowed\n");
   fprintf(stderr,"2-72 characters allowed\n");
   fprintf(stderr,"Only printable characters allowed\n");
   fprintf(stderr,"Only 0x21 to 0x7e are allowed\n");
   fprintf(stderr,"0x00 to 0x20 and 0x7f to 0xff "
      "are not allowed\n");
   exit(1);
   } /* putstx */

/* generate a uniform random number from 0 to 2^BITS */
unsigned int gen_token(xxfmt *xx, etfmt *et)
   {
   int indx;
   unsigned int x;
   indx = etausint(et,xx->alflen);
   x = (unsigned int) xx->alf[indx];
   xx->count++;
   return(x);
   } /* gen_token */

/* build a random template queue */
/* if BITS is equal to 3, each token is a binary */
/* number from zero to 7 */
void bldtmplt(xxfmt *xx, etfmt *et)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = gen_token(xx,et);
      pushq(xx->tmplthead, x);
      } /* for each element in template FIFO queue */
   } /* bldtmplt */

/* Create the initial sample queue the same size as */
/* the template */
/* the tokens in this sample queue should not match */
/* the template queue.  */
void bldlst(xxfmt *xx, etfmt *et)
   {
   int i;
   i = TMPLTSZ;
   while (i--)
      {
      unsigned int x;
      x = gen_token(xx,et);
      pushq(xx->lsthead, x);
      } /* for each element in active list FIFO queue */
   } /* bldlst */

/* update the sample FIFO queue with a new sample */
/* compare the sample queue to the template queue */
/* to see if a wrap-around error has occurred */
/* update the tally array based on the number of */
/* sample tokens that match the template */

void sample(xxfmt *xx, etfmt *et)
   {
   unsigned int newnum;
   popq(xx->lsttail);
   newnum = gen_token(xx,et);
   pushq(xx->lsthead, newnum);
   tally(xx);
   } /* sample */

int main(int argc, char **argv)
   {
   int i;
   int rslt;
   xxfmt *xx;
   etfmt *et;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   et = (etfmt *) etausinit();
   /****************************************************/
   /* Accept alfabet parameter                         */
   /****************************************************/
   if (argc != 2) putstx(*argv);
   strcpy(xx->alf,*(argv+1));
   rslt = ckalf(xx);
   if (rslt) putstx(*argv);
   fprintf(stderr,"Alfabet len=%d\n", xx->alflen);
   fprintf(stderr,"%s\n", xx->alf);
   /****************************************************/
   /* initialize queues and numeric fields             */
   /****************************************************/
   qsetup(xx);    /* init queues and numeric fields */
   bldtmplt(xx,et);   /* build template queue */
   bldlst(xx,et);     /* build sample queue   */
   i = SMPLS;
   while(i--)
      {
      /* take one sample                               */
      /* compare sample queue to template queue        */
      sample(xx,et);     /* take one sample */
      } /* for each sample */
   alfchisq(xx);    /* run chi square test on tallies */
   free(et->state);
   free(et);
   freeall(xx);    /* free all allocated memory */
   return(0);
   } /* main */
