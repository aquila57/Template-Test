#  libtmplt.mak - Compile template subroutine library Version 0.1.0
#  Copyright (C) 2020 aquila57 at github.com

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

OBJ=bld_maxint.o \
	calcchi.o \
	diepfx.o \
	freeall.o \
	getbyte.o \
	getdie.o \
	popq.o \
	pushq.o \
	qinit.o \
	qsetup.o \
	shwactual.o \
	shwlist.o \
	shwqueue.o \
	tally.o

CC=gcc

AR=ar

CFLAGS=-c -Wall -O2

LDFLAGS=

libtmplt.a:			$(OBJ)
		rm -f libtmplt.a
		$(AR) r libtmplt.a $(OBJ)

bld_maxint.o:			bld_maxint.c
		$(CC) $(CFLAGS) bld_maxint.c

calcchi.o:			calcchi.c
		$(CC) $(CFLAGS) calcchi.c

diepfx.o:			diepfx.c
		$(CC) $(CFLAGS) diepfx.c

freeall.o:			freeall.c
		$(CC) $(CFLAGS) freeall.c

getbyte.o:			getbyte.c
		$(CC) $(CFLAGS) getbyte.c

getdie.o:			getdie.c
		$(CC) $(CFLAGS) getdie.c

popq.o:				popq.c
		$(CC) $(CFLAGS) popq.c

pushq.o:			pushq.c
		$(CC) $(CFLAGS) pushq.c

qinit.o:			qinit.c
		$(CC) $(CFLAGS) qinit.c

qsetup.o:			qsetup.c
		$(CC) $(CFLAGS) qsetup.c

shwactual.o:			shwactual.c
		$(CC) $(CFLAGS) shwactual.c

shwlist.o:			shwlist.c
		$(CC) $(CFLAGS) shwlist.c

shwqueue.o:			shwqueue.c
		$(CC) $(CFLAGS) shwqueue.c

tally.o:			tally.c
		$(CC) $(CFLAGS) tally.c

clean:
		rm -f $(OBJ) libtmplt.a
