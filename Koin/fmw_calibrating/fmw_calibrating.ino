#include <EEPROM.h>
#include "Hx711.h"
#include "OutputManager.h"

//~ #define k1 46.5
//~ #define k2 56
//~ #define k3 112
//~ 
//~ #define expectedW (k3*2 + k2 + k1*2 - k1)//-- 26

#define ADDR_K1                          1
#define ADDR_K1_P                        2
#define ADDR_K2                          3
#define ADDR_K2_P                        4
#define ADDR_K3                          5
#define ADDR_K3_P                        6
#define ADDR_EXPECTED_WH                 7
#define ADDR_EXPECTED_WL                 8
#define ADDR_EXPECTED_WP                9
#define ADDR_EXPECTED_TOLERANCE_LOWER    10
#define ADDR_EXPECTED_TOLERANCE_UPPER    11



#define RELAYPIN A2
static float Weight=0;
static float vExpectedW;
static float vExpectedTL;
static float vExpectedTU;
static float vExpectedMin;
static float vExpectedMax;


Hx711 *scale;//(A0,A1);//-- param: A0-data 	A1-sck
Outputs output;

void RelayTes(Outputs *o)
{
	o->clearAll();
	delay(1000);
	o->setAll();
}
void RelayON(Outputs *o)
{
	o->clearAll();
}
void RelayOFF(Outputs *o)
{
	o->setAll();
}
int ReadSerial()
{
	int result;
	Serial.flush();
	delay(5);
	result = Serial.parseInt();
	return result;
}

void Calibrate()
{
	bool advance=true;
	while (advance)
	{
		Serial.println("command: ID VALUE");
		Serial.println("example \"1 300.50\" will set the weight expected to 300.5");
		Serial.println("1 WeightExpected");
		Serial.println("2 UpperTolerance");
		Serial.println("3 LowerTolerance");
		Serial.println("9 Quit Calibration");
		Serial.flush();
		int baca = Serial.parseInt();
		while (baca!=1 && baca!=2 && baca!=3 && baca!=9)
		{
			baca = Serial.parseInt();
			delay(50);
		}
		if (baca==9)
			return;
			
		while (!Serial.available()) delay(50);
		float value = Serial.parseFloat();
		delay(100);
		Serial.print(value);
		Serial.print(" for ");
		switch (baca)
		{
			case 1:
				Serial.println("Weight expected");break;
			case 2:
				Serial.println("Upper tolerance");break;
			case 3:
				Serial.println("Lower tolerance");break;
			default:
				break;
		}
		Serial.println(" is that ok?");
		Serial.println(" \t\t1: Execute");
		Serial.println(" \t\t9: Back/Cancel");
		int confirm;
		Serial.flush();
		confirm = Serial.parseInt();
		while (confirm!=1 && confirm!=9)
		{
			confirm = Serial.parseInt();
			delay(50);
		}
		
		if (confirm==1)
		{
			if (baca==1)
			{
				uint16_t dec;
				uint8_t decH;
				uint8_t decL;
				uint8_t point;
				dec = ((uint16_t)value);
				decH = dec>>8;
				decL = (uint8_t)(dec & 0x00ff);
				point = (uint8_t)((float)(value-(float)dec)*10);
				Serial.print("Writing: ");
				Serial.print(decH);
				Serial.print("<>");
				Serial.print(decL);
				Serial.print(" {.} ");
				Serial.println(point);
				
				EEPROM.write(ADDR_EXPECTED_WH, decH);
				EEPROM.write(ADDR_EXPECTED_WL, decL);
				EEPROM.write(ADDR_EXPECTED_WP, point);
				vExpectedW = value;
			}
			else if (baca==2)
			{
				EEPROM.write(ADDR_EXPECTED_TOLERANCE_UPPER, (uint8_t)value);
				Serial.print((uint8_t)value);
				Serial.println(" written");
				vExpectedTU = (uint8_t)value;
			}
			else if (baca==3)
			{
				EEPROM.write(ADDR_EXPECTED_TOLERANCE_LOWER, (uint8_t)value);
				Serial.print((uint8_t)value);
				Serial.println(" written");
				vExpectedTL = (uint8_t)value;
			}
			
			vExpectedMin = vExpectedW-vExpectedTL;
			vExpectedMax = vExpectedW+vExpectedTU;
		}
		baca = 0;
		delay(1000);
	}
}

void setup()
{
	Serial.begin(9600);
	delay(3000);
	Serial.println("hai");
	scale = new Hx711(A0,A1);
	output.add(A2);
	output.add(A3);
	RelayTes(&output);
	
	uint8_t decH,decL,point;
	uint16_t dec;
	decH = EEPROM.read(ADDR_EXPECTED_WH);
	decL = EEPROM.read(ADDR_EXPECTED_WL);
	dec = (decH<<8)+decL;
	point = EEPROM.read(ADDR_EXPECTED_WP);
	vExpectedW = ((float)dec) + (((float)point)/10);
	vExpectedTL = (float)EEPROM.read(ADDR_EXPECTED_TOLERANCE_LOWER);
	vExpectedTU = (float)EEPROM.read(ADDR_EXPECTED_TOLERANCE_UPPER);
	vExpectedMin = vExpectedW-vExpectedTL;
	vExpectedMax = vExpectedW+vExpectedTU;
	
	pinMode(7,INPUT);
	digitalWrite(7,HIGH);
}

void loop()
{
    if (digitalRead(7)==LOW)
		Calibrate();
    
    Weight = scale->getGram();
    float selisih;
    selisih = Weight - vExpectedW;
    
    Serial.print(Weight,1);
    Serial.print(" ");
    Serial.print(selisih,1);
    Serial.print(" ");
    Serial.print(vExpectedW,1);
    Serial.print(" =[[== ");
    Serial.print(vExpectedMin,1);
    Serial.print("~");
    Serial.print(vExpectedMax,1);
    
    Serial.println(" g");
    if (Weight>=vExpectedMin && Weight<=vExpectedMax)
    {
        delay(1000);
        Weight = scale->getGram();
		if (Weight>=vExpectedMin && Weight<=vExpectedMax)
        {
          Serial.println(" Succeed");
          RelayON(&output);
          delay(500);
        }
        else
        {
			RelayOFF(&output);
        }
    }
    else
    {
		RelayOFF(&output);
	}
    delay(200);
}


