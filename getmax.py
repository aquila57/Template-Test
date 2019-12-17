#!/usr/bin/python3
import sys,string
lst = sys.stdin.readlines()
maxnum = -999999
strt = 0
for ln in lst:
	ln = ln[0:-1]
	fld = ln.split()
	lgth = len(fld)
	if lgth == 2:
		numbit = fld[0]
		if numbit == "numbit:":
			strt = 1
			continue
	if strt == 1:
		num = int(fld[0])
		if num > maxnum:
			maxnum = num
hexnum = hex(maxnum)
print(maxnum, hexnum)
