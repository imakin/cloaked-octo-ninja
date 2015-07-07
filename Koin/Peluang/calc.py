satu = [46.7,  46.5,  46.5,  46.4,  47.8]
lima = [57.0,  57.0,  54.9,  57.5,  56.4]
sepuluh=[111.0, 112.0, 112.3, 114.1, 110.8]
hasil = []

def total(x):
	return (x[0]+x[1]+x[2]+x[3]+x[4])

#kombinasi
#satu*1 lima*1 sepuluh*2
for i in satu:
	for j in lima:
		None
		for a in range(0,3):
			for b in range(a+1,4):
				t =  (i + j + sepuluh[a] + sepuluh[b])
				hasil.append(t)
				if (t<280):
					print (str(i) +" + "+ str(j) +" + "+ str(sepuluh[a])+" + "+str(sepuluh[b]))
				#~ print t
		#~ t =  (i + j + sepuluh[0] + sepuluh[1])
		#~ t =  (i + j + sepuluh[0] + sepuluh[2])
		#~ t =  (i + j + sepuluh[0] + sepuluh[3])
		#~ t =  (i + j + sepuluh[0] + sepuluh[4])
		#~ t =  (i + j + sepuluh[1] + sepuluh[2])
		#~ t =  (i + j + sepuluh[1] + sepuluh[3])
		#~ t =  (i + j + sepuluh[1] + sepuluh[4])
		#~ t =  (i + j + sepuluh[2] + sepuluh[3])
		#~ t =  (i + j + sepuluh[2] + sepuluh[4])
		#~ t =  (i + j + sepuluh[3] + sepuluh[4])
		

#satu*1 lima*3 sepuluh*1
for i in satu:
	for j in sepuluh:
		t =  (i + j + lima[0]+lima[1]+lima[2])
		t =  (i + j + lima[0]+lima[1]+lima[3])
		t =  (i + j + lima[0]+lima[1]+lima[4])
		t =  (i + j + lima[0]+lima[2]+lima[3])
		t =  (i + j + lima[0]+lima[2]+lima[4])
		t =  (i + j + lima[0]+lima[3]+lima[4])
		t =  (i + j + lima[1]+lima[2]+lima[3])
		t =  (i + j + lima[1]+lima[2]+lima[4])
		t =  (i + j + lima[1]+lima[3]+lima[4])
		t =  (i + j + lima[2]+lima[3]+lima[4])


#satu*1 lima*5 sepuluh*0
for i in satu:
	t =  (i+total(lima))

hasil = sorted(hasil)
LUT = "{"
for i in range(len(hasil)):
	LUT = LUT + str(hasil[i]) + ", "
print LUT[:-2]+"}"
