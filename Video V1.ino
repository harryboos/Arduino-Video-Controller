#include <IRremote\IRremote.h>
IRsend irsend;
int touch = 2;
unsigned int p_button[67] = { 8900,4500,550,550,500,650,500,550,550,600,500,600,550,550,550,600,500,1700,550,1700,500,1750,500,1700,550,1700,500,1700,550,1700,550,1700,500,600,500,600,500,1750,500,1700,550,1700,500,1700,600,550,500,600,500,600,550,1700,500,600,550,600,500,600,500,600,550,1700,500,1700,550,1700,500 };

void setup()
{
  pinMode(touch, INPUT);
}

void loop()
{
  if (digitalRead(touch) == HIGH)
	{
		irsend.sendRaw(p_button, 67, 38);
		delay(500);
		irsend.sendRaw(p_button, 67, 38);
	}
  delay(1000);
}
