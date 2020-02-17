/* tmplate.h - Template Test Program Header  Version 0.1.0 */
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

/* The template programs use the GNU Scientific Library to           */
/* set initial random seeds, and to                                  */
/* calculate P-value and chi square range.                           */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>

/* number of random samples in test */

#define SMPLS (10000000)

/* modulus used in srndtmplt.c */

#define MOD 1000000000

/* template size is large enough, so that it should never */
/* be completely matched.                                 */
/* To completely match the template, conduct a separate   */
/* test where the data is repeated after 10000 samples.   */
/* This will force a wrap-around error.                   */
/* Programs randu16.c and lfsr16.c are designed to        */
/* produce the wrap-around error.                         */
/* To force a chi square failure, use a poor generator,   */
/* like a fibonacci, randu, plain lfsr, or sine wave      */
/* generator.                                             */

#define TMPLTSZ 1024

/* BITS is the number of bits in each token in the template */
/* A 3 bit number is 0-7 */
/* BITS should be 2 to 32 */

#define BITS 3

/* MAXINT is pow(2.0,32.0) */

#define MAXINT (4294967296.0)

/* queue structure */
/* The template is stored as a FIFO queue. */
/* The samples are stored in a separate FIFO queue */
/* to match against the template queue. */

typedef struct qstruct {
   struct qstruct *next;
   struct qstruct *prev;
   unsigned int num;
   } qfmt;

/* These are re-entrant programs.  All data is stored */
/* in a dynamic structure on the heap. */

typedef struct xxstruct {
   qfmt *tmplthead;         /* head of the template queue */
   qfmt *tmplttail;         /* tail of the template queue */
   qfmt *lsthead;           /* head of the sample   queue */
   qfmt *lsttail;           /* tail of the sample   queue */
   gsl_rng_type *typ;      /* GSL random generator type   */
   gsl_rng *rng;           /* GSL random number generator */
   char alf[256];              /* ASCII alfabet */
   int alflen;                 /* length of alfabet */
   int eofsw;                  /* end of file switch */
   int generator;              /* Dieharder generator number */
   int state[55];              /* Knuth subrand state */
   int si;                     /* index into state[] */
   int sj;                     /* index into state[] */
   unsigned int dttk;          /* date,time,ticks */
   unsigned int count;         /* token count */
   unsigned int fibonum1;      /* fibonacci seed */
   unsigned int fibonum2;      /* fibonacci seed */
   unsigned int fibonum3;      /* fibonacci seed */
   unsigned int seed;          /* randu seed */
   unsigned int lfsr0;         /* high order LFSR */
   unsigned int lfsr;          /* low  order LFSR */
   unsigned int major;         /* high order LFSR */
   unsigned int minor;         /* low  order LFSR */
   unsigned int out;           /* LFSR output bit */
   unsigned int lowbit;        /* low bit of lfsr0 */
   double modulus;             /* 32 bit modulus 2^32 */
   double onepi;               /* constant value of M_PI */
   double maxint;              /* double precision MAXINT */
   double dbllmt;              /* double precision 2^BITS */
   /* array of actual sample tallies */
   /* The index to the array is the number of times that  */
   /* sample tokens are matched against the template.     */
   double actual[TMPLTSZ];
   double maxint_tbl[2048];
   double chisq;            /* chi square result */
   double pvalue;           /* P-value of chi square test */
   } xxfmt;

/* Build maxint table */
void bld_maxint(xxfmt *xx);

/* Initialize queues and numeric fields */
void qsetup(xxfmt *xx);

/* Initialize a new element in a FIFO queue */
qfmt *qinit(void);

/* FIFO queue push */
void pushq(qfmt *head, unsigned int num);

/* FIFO queue pop */
void popq(qfmt *tail);

/* debugging routine to display the template queue */
void shwqueue(xxfmt *xx);

/* debugging routine to display the actual sample queue */
void shwlist(xxfmt *xx);

/* debugging routine to display the actual tally array */
void shwactual(xxfmt *xx);

/* Starting with the tail of each queue, */
/* compare the sample queue against the template queue */
/* The number of token matches is the index into the */
/* actual tally array. */
/* If the number of token matches is equal to TMPLTSZ */
/* a wrap-around error occurs, and the template test */
/* fails. */

void tally(xxfmt *xx);

/* run a chi square test on the tally array */
void calcchi(xxfmt *xx);

/* bypass Dieharder prefix */
void diepfx(xxfmt *xx);

/* read one line from Dieharder */
int getdie(xxfmt *xx);

/* read one byte from stdin */
int getbyte(void);

/* free all allocated memory */
void freeall(xxfmt *xx);

/* Knuth subrand generator initialization routine */
void subrand_seed(xxfmt *xx, int p1);

/* Knuth subrand generator */
int subrand(xxfmt *xx);

/* validate alfabet in alftmplt.c */
int ckalf(xxfmt *xx);

/* Chi square test for alftmplt.c */
void alfchisq(xxfmt *xx);
