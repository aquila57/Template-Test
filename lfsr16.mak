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

OBJ=lfsr16.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-L. -ltmplt -lgsl -lgslcblas -lm

lfsr16:				$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o lfsr16 $(LDFLAGS)

lfsr16.o:			lfsr16.c
		$(CC) $(CFLAGS) lfsr16.c

clean:
		rm -f $(OBJ) lfsr16
