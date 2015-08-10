/*****************************************************************************/
//	Function: control the seeedstudo Grove MP3 player
//      Hardware: Grove - Serial MP3 Player
/*******************************************************************************/
#include <SoftwareSerial.h>

static int cmd;
static uint16_t playID;

SoftwareSerial mp3(2, 3);//modify this with the connector you are using.
void setup()
{
	delay(3000);
	mp3.begin(9600);
	Serial.begin(9600); 
	delay(1000);
	Serial.println("Mulai");
	if (true ==SetPlayMode(0x01))
		Serial.println("Set The Play Mode to 0x01, Single Loop Mode.");
	else
		Serial.println("Playmode Set Error");
	//~ PauseOnOffCurrentMusic();
	playID = 1;
}
void loop()
{
	SetPlayMode(0x01);
	delay(1000);
	SetMusicPlay(00,01);
	delay(1000);
	SetVolume(0x0E);
	while(1)
	{
		//~ Serial.println("waiting");
		while (Serial.available()>0)
		{
			cmd = Serial.parseInt();
			if (Serial.read()=='\n') {
				delay(1000);
				playID = (uint16_t)cmd;
				
				SetPlayMode(2);
				delay(1000);
				SetVolume(0x0E);
				delay(1000);
				
				SetMusicPlay((uint8_t)(playID>>8),(uint8_t)playID);
				Serial.print("Play set to ");
				Serial.print((uint8_t)(playID>>8),DEC);
				Serial.print(" ");
				Serial.print((uint8_t)playID,DEC);
				Serial.print(" (");
				Serial.print(playID,DEC);
				Serial.print(" )\n");
				delay(1000);
			}
		}
		delay(50);
	}
}
//Set the music index to play, the index is decided by the input sequence
//of the music;
//hbyte: the high byte of the index;
//lbyte: the low byte of the index;
boolean SetMusicPlay(uint8_t hbyte,uint8_t lbyte)
{
	mp3.write(0x7E);
	mp3.write(0x04);
	mp3.write(0xA0);
	mp3.write(hbyte);
	mp3.write(lbyte);
	mp3.write(0x7E);
	delay(10);
	while(mp3.available())
	{
		if (0xA0==mp3.read())
			return true;
		else 
			return false;
	}
}
// Pause on/off  the current music
boolean PauseOnOffCurrentMusic(void)
{
	mp3.write(0x7E);
	mp3.write(0x02);
	mp3.write(0xA3);
	mp3.write(0x7E);
	delay(10);
	while(mp3.available())
	{
		if (0xA3==mp3.read())
			return true;
		else 
			return false;
	}
}

//Set the volume, the range is 0x00 to 0x1F
boolean SetVolume(uint8_t volume)
{
	mp3.write(0x7E);
	mp3.write(0x03);
	mp3.write(0xA7);
	mp3.write(volume);
	mp3.write(0x7E);
	delay(10);
	while(mp3.available())
	{
		if (0xA7==mp3.read())
			return true;
		else 
			return false;
	}
}

boolean SetPlayMode(uint8_t playmode)
{
	if (((playmode==0x00)|(playmode==0x01)|(playmode==0x02)|(playmode==0x03))==false)
	{
		Serial.println("PlayMode Parameter Error! ");
		return false;
	}
	mp3.write(0x7E);
	mp3.write(0x03);
	mp3.write(0xA9);
	mp3.write(playmode);
	mp3.write(0x7E);
	delay(10);
	uint8_t maxloop = 10;
	while(mp3.available())
	{
		Serial.println("w8");
		if (maxloop>1)
		{
			uint8_t r;
			r = mp3.read();
			Serial.println(r,DEC);
			if (0xA9==r)
				return true;
			else
				maxloop = maxloop-1;
		}
		else
		{
			return false;
		}
		delay(100);
	}
}
