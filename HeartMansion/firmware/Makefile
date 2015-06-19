
BOARD_TAG = leonardo
ARDUINO_LIBS =
all:
	
flashlangsung :
	sudo avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -cusbasp -Pusb -Uflash:w:$(TARGET_HEX):i
include ../../Arduino.mk
