/* bld_maxint.c - Build MAXINT Table  Version 0.1.0 */
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

/* This program builds the maxint_tbl  */

void bld_maxint(xxfmt *xx)
   {
   double *p,*q;
   /***********************************************/
   /* zero fill the maxint table                  */
   /***********************************************/
   p = (double *) xx->maxint_tbl;
   q = (double *) xx->maxint_tbl + 2048;
   while (p < q) *p++ = 0.0;
   p = (double *) xx->maxint_tbl;
   *p++ = 0xffffffff;     /* 000 borosh13 */
   *p++ = 0x7fffffff;     /* 001 cmrg */
   *p++ = 0xffffffff;     /* 002 coveyou */
   *p++ = 0x7fffffff;     /* 003 fishman18 */
   *p++ = 0x7fffffff;     /* 004 fishman20 */
   *p++ = 0x7fffffff;     /* 005 fishman2x */
   *p++ = 0xffffffff;     /* 006 gfsr4 */
   *p++ = 0x3fffffff;     /* 007 knuthran */
   *p++ = 0x7fffffff;     /* 008 knuthran2 */
   *p++ = 0x3fffffff;     /* 009 knuthran2002 */
   *p++ = 0x7fffffff;     /* 010 lecuyer21 */
   *p++ = 0x7fffffff;     /* 011 minstd */
   *p++ = 0x7fffffff;     /* 012 mrg */
   *p++ = 0xffffffff;     /* 013 mt19937 */
   *p++ = 0xffffffff;     /* 014 mt19937_1999 */
   *p++ = 0xffffffff;     /* 015 mt19937_1998 */
   *p++ = 0xffffffff;     /* 016 r250 */
   *p++ = 0x7fffffff;     /* 017 ran0 */
   *p++ = 0x7fffffff;     /* 018 ran1 */
   *p++ = 0x7fffffff;     /* 019 ran2 */
   *p++ = 999999999;      /* 020 ran3 */
   *p++ = 0x7fffffff;     /* 021 rand */
   *p++ = 0xffffffff;     /* 022 rand48 */
   *p++ = 0x7fffffff;     /* 023 random128-bsd    */
   *p++ = 0x7fffffff;     /* 024 random128-glibc2 */
   *p++ = 0x7fffffff;     /* 025 random128-libc5  */
   *p++ = 0x7fffffff;     /* 026 random256-bsd    */
   *p++ = 0x7fffffff;     /* 027 random256-glibc2 */
   *p++ = 0x7fffffff;     /* 028 random256-libc5  */
   *p++ = 0x7fffffff;     /* 029 random32-bsd     */
   *p++ = 0x7fffffff;     /* 030 random32-glibc2  */
   *p++ = 0x7fffffff;     /* 031 random32-libc5   */
   *p++ = 0x7fffffff;     /* 032 random64-bsd     */
   *p++ = 0x7fffffff;     /* 033 random64-glibc2  */
   *p++ = 0x7fffffff;     /* 034 random64-libc5   */
   *p++ = 0x7fffffff;     /* 035 random8-bsd      */
   *p++ = 0x7fffffff;     /* 036 random8-glibc2   */
   *p++ = 0x7fffffff;     /* 037 random8-libc5    */
   *p++ = 0x7fffffff;     /* 038 random-bsd       */
   *p++ = 0x7fffffff;     /* 039 random-glibc2    */
   *p++ = 0x7fffffff;     /* 040 random-libc5     */
   *p++ = 0x7fffffff;     /* 041 randu */
   *p++ = 0xffffffff;     /* 042 ranf */
   *p++ = 0xffffff;       /* 043 ranlux */
   *p++ = 0xffffff;       /* 044 ranlux389 */
   *p++ = 0xffffffff;     /* 045 ranlxd1 */
   *p++ = 0xffffffff;     /* 046 ranlxd2 */
   *p++ = 0xffffff;       /* 047 ranlxs0 */
   *p++ = 0xffffff;       /* 048 ranlxs1 */
   *p++ = 0xffffff;       /* 049 ranlxs2 */
   *p++ = 0xffffff;       /* 050 ranmar */
   *p++ = 0x3fffff;       /* 051 slatec */
   *p++ = 0xffffffff;     /* 052 taus */
   *p++ = 0xffffffff;     /* 053 taus2 */
   *p++ = 0xffffffff;     /* 054 taus113 */
   *p++ = 0xffffffff;     /* 055 transputer */
   *p++ = 0xffffffff;     /* 056 tt800 */
   *p++ = 0xffff;         /* 057 uni */
   *p++ = 0x7fffffff;     /* 058 uni32 */
   *p++ = 0xffffffff;     /* 059 vax */
   *p++ = 0xffffffff;     /* 060 waterman14 */
   *p++ = 0xffffff;       /* 061 zuf */
   p = (double *) xx->maxint_tbl + 203;
   *p++ = 0xffffffff;     /* 203 ca */
   *p++ = 0xffffffff;     /* 204 uvag */
   *p++ = 0xffffffff;     /* 205 AES_OFB */
   *p++ = 0xffffffff;     /* 206 Threefish_OFB */
   *p++ = 0xffffffff;     /* 207 XOR (supergenerator) */
   *p++ = 0xffffffff;     /* 208 kiss */
   *p++ = 0xffffffff;     /* 209 superkiss */
   p = (double *) xx->maxint_tbl + 400;
   *p++ = 0xffffffff;     /* 400 R_wichmann_hill */
   *p++ = 0xffffffff;     /* 401 R_marsaglia_multic. */
   *p++ = 0xffffffff;     /* 402 R_super_duper */
   *p++ = 0xffffffff;     /* 403 R_mersenne_twister */
   *p++ = 0x3fffffff;     /* 404 R_knuth_taocp */
   *p++ = 0x3fffffff;     /* 405 R_knuth_taocp2 */
   } /* bld_maxint */
