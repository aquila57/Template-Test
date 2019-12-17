/* calcchi.c - Run a chi square test  Version 0.1.0 */
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

/* run a chi square test on the tally array */

void calcchi(xxfmt *xx)
   {
   int indx;
   double prob;        /* probability of each tally */
   double expected;    /* expected number of tallies */
   double diff;        /* actual minus expected */
   double diffsq;      /* tally difference squared */
   double max;         /* 2^BITS                   */
   double totsmpls;    /* total number of samples */
   double df;          /* degrees of freedom */
   double minchi;      /* minimum chi square at 95% */
   double maxchi;      /* maximum chi square at 95% */
   printf(" Matches     Actual          "
      "Expected             Difference\n");
   max = (double) (1 << BITS);
   totsmpls = (double) SMPLS;
   xx->chisq = 0.0;    /* initialize chi square */
   /* probability of no match */
   prob = 1.0 - (1.0 / max);
   indx = 0;
   /* for each tally in the tally array greater than 10 */
   while (xx->actual[indx] > 10)
      {
      /* expected number of tallies */
      expected = prob * totsmpls;
      /* difference between actual and expected tallies */
      diff = xx->actual[indx] - expected;
      diffsq = diff * diff;     /* difference squared */
      /* add to the chi square */
      xx->chisq += (diffsq / expected);
      /* running display of the actual and expected */
      printf("%5d     %9.0f     %15.5f      %15.5f\n",
         indx, xx->actual[indx], expected, diff);
      /* calculate the probability and expected values */
      /* for the next tally in the tally array */
      prob /= max;
      expected = prob * totsmpls;
      indx++;
      } /* for each level of actual tally */
   /* calculate degrees of freedom */
   df = (double) (indx - 1);
   minchi = gsl_cdf_chisq_Pinv(0.025,df);
   maxchi = gsl_cdf_chisq_Pinv(0.975,df);
   xx->pvalue = gsl_cdf_chisq_P(xx->chisq,df);
   printf("Chi square %f  P-value %f\n", xx->chisq, xx->pvalue);
   printf("At 95%c probability and %.0f degrees of freedom,\n"
      "Chi square ranges from %f to %f\n",
      '%', df, minchi, maxchi);
   } /* calcchi */
