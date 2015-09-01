#!/usr/bin/env python
#-- @author: Makin, August 2015
from RPi import GPIO
import time
import os
import subprocess
import re

SAMPLE_SIZE = 256
IRpin = 14
GPIO.setmode(GPIO.BCM)
GPIO.setup(IRpin, GPIO.IN)
def kill():
	proses = "omxplayer"
	hasiltm = os.popen("ps -ef | grep "+proses).read()[:-1]
	print hasiltm
	namauser = os.popen("whoami").read()[:-1]
	prosesid = hasiltm.lstrip(namauser).lstrip(" ")[ :hasiltm.lstrip(namauser).lstrip(" ").find(" ") ]
	os.system("kill -9 "+prosesid)

def kill2():
	print (os.popen("date > /home/pi/remoteTV/killlog"))
	
	proses = "omxplayer"
	hasiltm = os.popen("ps ax | grep -v grep | grep omxplayer").read()[:-1]
	pids = re.findall('(\\d+).+', hasiltm)
	process = ""
	for pid in pids:
		process = process + pid + " "
	print process
	os.system("sudo kill -9 "+process)
	

lastLow = 0.0
lastHigh = 0.0
directions = []

def method2():
	lowNum =0
	highNum = 0
	while (True):
		cc = 0
		while (cc<SAMPLE_SIZE):
			if (GPIO.input(IRpin)==1):
				highNum += 1
			else:
				lowNum += 1
			
			cc+= 1
		#~ if (lowNum>highNum):
		if (lowNum>=SAMPLE_SIZE):
			print (highNum, lowNum)
			kill2()
			time.sleep(3)
		highNum=0
		lowNum=0
method2()

GPIO.cleanup()
