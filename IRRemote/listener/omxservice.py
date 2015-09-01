#!/usr/bin/env python
#-- @author: Makin, August 2015
import time
import os
import subprocess
#import thread

def omxservice():
	while (True):
		if (os.popen("ps ax | grep -v grep | grep omxplayer").read()==''):
			subprocess.Popen("omxplayer /home/pi/tvchannel.mov --loop --no-keys", shell=True, stdin=subprocess.PIPE)
		else:
			time.sleep(1)
omxservice()			
#thread.start_new_thread( omxservice, () )

#while (True):pass
