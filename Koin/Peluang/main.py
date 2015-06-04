#!/usr/bin/env python3
import sys
def echo(s):
	sys.stdout.write(s)
a = 1
b = 5
c = 10
#~ a = 90
#~ b = 160
#~ c = 230

ax = 27
bx = 0
cx = 0
hasil = []
#~ hasilline = []
while(ax>0):
	if (a*ax + b*bx + c*cx)==a*27:
		#~ print(a,ax,' ',b,bx,' ',c,cx)
		hasilline = [a,ax,b,bx,c,cx]
		hasil.append(hasilline)
	cx = 0
	ax -= int(b/a)
	bx += 1
	t = bx
	while (bx>=0 and ax>0):
		if (a*ax + b*bx + c*cx)==a*27:
			#~ print(a,ax,' ',b,bx,' ',c,cx)
			hasilline = [a,ax,b,bx,c,cx]
			hasil.append(hasilline)
		bx -= int(c/b)
		cx += 1
	bx = t
		
		
print (hasil)
#-- checkout how real weight affects
k1 = 90
k2 = 450
k3 = 900
for h in hasil:
	a	= h[0]
	ax	= h[1]
	b	= h[2]
	bx	= h[3]
	c	= h[4]
	cx	= h[5]
	print(a,ax,' ',b,bx,' ',c,cx)
	print('real weight ',k1*ax + k2*bx + k3*cx)
