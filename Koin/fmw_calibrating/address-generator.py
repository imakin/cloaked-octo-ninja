#!/usr/bin/env python3
import sys,os
num = 1
maxl = 0
prefix = "ADDR_"
try:
	prefix = sys.argv[2]
except:pass
with open(sys.argv[1]) as addr:
	for t in addr:
		if len(t)>maxl:
			maxl = len(t)+2
			
with open(sys.argv[1]) as addr:
	for t in addr:
		print("#define",
				" ",
				prefix,
				t[:-1].ljust(maxl),
				" ",
				num,
				sep="")
		num += 1
