#!/usr/bin/env python
#-- Makin, 2015
from RPi import GPIO
import time
import os
import subprocess
import sys

SAMPLE_SIZE = 256
SENSOR_PIN = 4
GPIO.setmode(GPIO.BCM)
GPIO.setup(SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

try:
	while (True):
		masukan = GPIO.input(SENSOR_PIN)
		if (masukan==1):
			time.sleep(0.5)
			masukan = GPIO.input(SENSOR_PIN)
			if (masukan==1):
				os.system('omxplayer /home/pi/pintuSound/resource/glass.mp3')
				while (GPIO.input(SENSOR_PIN)==1):
					time.sleep(0.5)
		time.sleep(0.2)
finally:
	GPIO.cleanup()

