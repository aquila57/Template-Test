#  lfsr16.mak - Compile lfsr16.c Version 0.1.0
#  Copyright (C) 2019 aquila57 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

#--------------------------------------------------------
# The LFSR in this generator comes from the following
# http://courses.cse.tamu.edu/walker/csce680/
# lfsr_table.pdf
#--------------------------------------------------------

OBJ=lfsr16.o \
	qsetup.o \
	qinit.o \
	pushq.o \
	popq.o \
	shwqueue.o \
	shwlist.o \
	shwactual.o \
	tally.o \
	calcchi.o \
	freeall.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lgsl -lgslcblas -lm

lfsr16:				$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o lfsr16 $(LDFLAGS)

lfsr16.o:			lfsr16.c
		$(CC) $(CFLAGS) lfsr16.c

qsetup.o:			qsetup.c
		$(CC) $(CFLAGS) qsetup.c

qinit.o:			qinit.c
		$(CC) $(CFLAGS) qinit.c

pushq.o:			pushq.c
		$(CC) $(CFLAGS) pushq.c

popq.o:				popq.c
		$(CC) $(CFLAGS) popq.c

shwqueue.o:			shwqueue.c
		$(CC) $(CFLAGS) shwqueue.c

shwlist.o:			shwlist.c
		$(CC) $(CFLAGS) shwlist.c

shwactual.o:			shwactual.c
		$(CC) $(CFLAGS) shwactual.c

tally.o:			tally.c
		$(CC) $(CFLAGS) tally.c

calcchi.o:			calcchi.c
		$(CC) $(CFLAGS) calcchi.c

freeall.o:			freeall.c
		$(CC) $(CFLAGS) freeall.c

clean:
		rm -f $(OBJ) lfsr16
