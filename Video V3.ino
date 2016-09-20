#include <IRremote/IRremote.h>
//#include <Adafruit_CC3000_Library-master\Adafruit_CC3000.h>
//#include <Adafruit_CC3000_Library-master\ccspi.h>
//#include <SPI\SPI.h>
//#include <string.h>
//#include "Adafruit_CC3000_Library-master\utility\debug.h"
//#include "Adafruit_CC3000_Library-master\utility\sntp.h"
#include <Wire/Wire.h>
#include <math.h>
#include <elapsedMillis/elapsedMillis.h>

//#define Wido_IRQ 7                                                                        //define Wido-3000
//#define Wido_VBAT 5
//#define Wido_CS 10
//Adafruit_CC3000 Wido = Adafruit_CC3000(Wido_CS, Wido_VBAT, SPI_CLOCK_DIVIDER);

//#define WLAN_SSID "Robotics-Internal"                                                    //define WLAN
//#define WLAN_PASS "210.33.134.160"
//#define WLAN_SECURITY WLAN_SEC_WPA2
//#define TIMEOUT_MS 3000

//uint32_t ipAddress = Wido.IP2U32(192, 168, 1, 123);                                      //define static IP
//uint32_t netMask = Wido.IP2U32(255, 255, 255, 0);
//uint32_t defaultGateway = Wido.IP2U32(192, 168, 1, 1);
//uint32_t dns = Wido.IP2U32(8, 8, 8, 8);

//sntp mysntp = sntp(NULL, "time.nist.gov", (short)(+8 * 60), (short)(+8 * 60), false);    //define NTP time sever
//SNTP_Timestamp_t now;
//NetTime_t timeExtract;
//#define pF(string_pointer) (reinterpret_cast<const __FlashStringHelper *>(pgm_read_word(string_pointer)))

//const prog_char janStr[] PROGMEM = "January";                                           //define NTP time
//const prog_char febStr[] PROGMEM = "February";
//const prog_char marStr[] PROGMEM = "March";
//const prog_char aprStr[] PROGMEM = "April";
//const prog_char mayStr[] PROGMEM = "May";
//const prog_char junStr[] PROGMEM = "June";
//const prog_char julStr[] PROGMEM = "July";
//const prog_char augStr[] PROGMEM = "August";
//const prog_char sepStr[] PROGMEM = "September";
//const prog_char octStr[] PROGMEM = "October";
//const prog_char novStr[] PROGMEM = "November";
//const prog_char decStr[] PROGMEM = "December";

//PROGMEM const char * const monthStrs[] = 
//{ 
	//janStr, febStr, marStr, aprStr, mayStr, junStr, julStr, augStr, sepStr, octStr, novStr, decStr
//};

//const prog_char sunStr[] PROGMEM = "Sunday";
//const prog_char monStr[] PROGMEM = "Monday";
//const prog_char tueStr[] PROGMEM = "Tuesday";
//const prog_char wedStr[] PROGMEM = "Wednesday";
//const prog_char thuStr[] PROGMEM = "Thursday";
//const prog_char friStr[] PROGMEM = "Friday";
//const prog_char satStr[] PROGMEM = "Saturday";

//PROGMEM const char* const dayStrs[] = 
//{ 
	//sunStr, monStr, tueStr,  wedStr,thuStr, friStr, satStr
//};

IRsend irsend;
unsigned int n_button[67] = { 9000,4550,500,600,550,550,600,550,550,600,500,600,550,600,500,600,550,550,600,1700,500,1750,500,1700,600,1700,500,1750,500,1700,600,1700,500,1750,500,600,550,1700,550,600,500,1700,550,1700,600,550,550,600,500,600,550,1700,550,550,600,1700,500,600,550,600,500,1700,600,1700,500,1750,500 };
unsigned int p_button[67] = { 9000,4500,550,600,550,550,550,600,500,650,500,600,550,550,550,600,550,550,550,1750,500,1700,550,1700,550,1750,500,1700,550,1700,550,1750,500,1700,550,1700,550,1700,550,1700,550,600,550,550,550,600,500,650,500,600,550,550,550,600,550,550,550,1750,500,1700,550,1700,550,1750,500,1700,550 };
int BH1750address = 0x23;
byte buff[2];
int t = 0;
int s = 0;
elapsedMillis sinceTest1 = 0;

//uint16_t checkFirmwareVersion(void)
//{
	//uint8_t major, minor;
	//uint16_t version;
//#ifndef CC3000_TINY_DRIVER
	//if (!Wido.getFirmwareVersion(&major, &minor))
	//{
		//Serial.println(F("Unable to retrieve the firmware version!\r\n"));
		//version = 0;
	//}
	//else
	//{
		//Serial.print(F("Firmware V. : "));
		//Serial.print(major);
		//Serial.print(F("."));
		//Serial.println(minor);
		//version = major;
		//version <<= 8;
		//version |= minor;
	//}
//#endif // !CC3000_TINY_DRIVER
	//return version;
//}

int BH1750_Read(int address)
{
	int i = 0;
	Wire.beginTransmission(address);
	Wire.requestFrom(address, 2);
	while (Wire.available())
	{
		buff[i] = Wire.read();
		i++;
	}
	Wire.endTransmission();
	return i;
}

void BH1750_Init(int address)
{
	Wire.beginTransmission(address);
	Wire.write(0x10);
	Wire.endTransmission();
}

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	//Serial.println(F("\nInitialising the CC3000 ..."));
	//if (!Wido.begin())
	//{
		//Serial.println(F("Unable to initialise the CC3000!"));
		//while (1);
	//}
	//uint16_t firmware = checkFirmwareVersion();
	//if (firmware < 0x113)
	//{
		//Serial.println(F("Wrong firmware version!"));
		//for (;;);
	//}
	//Serial.println(F("\nDeleting old connection profiles"));
	//if (!Wido.deleteProfiles())
	//{
		//Serial.println(F("Failed!"));
		//while (1);
	//}
	//Serial.println(F("Connecting Router/AP"));
	//if (!Wido.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY))
	//{
		//Serial.println(F("Failed!"));
		//while (1);
	//}
	//Serial.println(F("Router  /AP Connected!"));
	
	//if (!Wido.setStaticIPAddress(ipAddress, netMask, defaultGateway, dns))
	//{
		//Serial.println(F("Failed to set static IP"));
		//while (1);
	//}
}

void loop()
{
	if (sinceTest1 > 0 & sinceTest1 < 2000)
    {
		sinceTest1 = 0;
    }
    int i;
	uint16_t val = 0;
	uint16_t j = 0;
	BH1750_Init(BH1750address);
	delay(1000);

	if (2 == BH1750_Read(BH1750address))
	{
		val = ((buff[0] << 8) | buff[1]) / 1.2;
		Serial.print(val, DEC);
		Serial.println("[lx]");
	}
	s = t - val;
	t = val;
    Serial.print("S: ");
    Serial.println(s);
	if (s > 5)
	{
		//Serial.println(F("UpdateNTPTime"));
		//mysntp.UpdateNTPTime();
		//Serial.println(F("Current local time is: "));
		//mysntp.ExtractNTPTime(mysntp.NTPGetTime(&now, true), &timeExtract);
		//Serial.print(timeExtract.hour);
		//Serial.print(F(":"));
		//Serial.print(timeExtract.min);
		//Serial.print(F(":"));
		//Serial.print(timeExtract.sec);
		//Serial.print(F("."));
		//Serial.println(timeExtract.millis);
		//Serial.print(pF(&dayStrs[timeExtract.wday]));
		//Serial.print(F(", "));
		//Serial.print(pF(&monthStrs[timeExtract.mon]));
		//Serial.print(F(" "));
		//Serial.print(timeExtract.mday);
		//Serial.print(F(", "));
		//Serial.println(timeExtract.year);
		//Serial.print(F("Day of year: "));
		//Serial.println(timeExtract.yday + 1);
		//if (timeExtract.hour < 17 & timeExtract.hour >8)
		//{
		BH1750_Init(BH1750address);
		delay(1000);

		if (2 == BH1750_Read(BH1750address))
		{
			j = ((buff[0] << 8) | buff[1]) / 1.2;
			Serial.print(j, DEC);
			Serial.println("[lx]");
		}
		if (j < 10)
		{
			sinceTest1 = 0;
			irsend.sendRaw(n_button, 67, 38);
			delay(2000);
		}
	}
    if (sinceTest1 > 100000)
	{
		irsend.sendRaw(p_button, 67, 38);
        sinceTest1 = 0;
	}
}
