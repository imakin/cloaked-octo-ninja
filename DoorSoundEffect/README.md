Pin GND dan BCM4 disambungkan ke sensor magnet,

Pin BCM4 telah di set ke Input dengan internal-pull-up
resistor. Bila pintu ditutup, BCM4 short dengan GND,
ketika pintu dibuka, BCM4 lepas dari GND dan suara akan 
terpicu. Suara hanya dibunyikan satu kali, hingga pintu
ditutup kembali sistem kembali berulang.

file suara pada folder resource, format mp3

penempatan file:

~/.config/autostart/doorservice.desktop

~/pintuSound/doorservice

~/pintuSound/doorservice.py

~/pintuSound/resource/glass.mp3
