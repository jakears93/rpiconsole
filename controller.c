#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <xdo.h>

void setup();
void run();
void buttonPress();

final int numOfButtons = 18;
bool keyAction[numOfButtons];
int pinNum[numOfButtons];
xdo_t* system = xdo_new(":0.0"); 
char* keyMap[numOfButtons] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r"};

int main(void)
{
	setup();
	run();
	return 0;
}

void setup()
{
	wiringPiSetupGpio();
	int i = 0;
	for (i; i<numOfButtons; i++)
	{
		pinNum[i] = i+1;
	}
	for (i; i<numOfButtons; i++)
	{
		pinMode(pinNum[i], INPUT);
		pullUpDnControl(pinNum[i], PUD_UP);	
	}
}

void run()
{
	bool button[numOfButtons];
	while(1)
	{
		int i = 0;
		for (i; i<numOfButtons; i++)
		{
			button[i] = digitalRead(pinNum[i]);
		}
		sleep(25);
		buttonPress(button);
	}
}

void buttonPress(bool button[numOfButtons])
{
	int i = 0;
	bool keyChange = false;
	for(i; i<numOfButtons; i++)
	{
		keyChange = false;
		if (keyAction[i] != button[i])
		{
			keyAction[i] = button[i];
			keyChange = true;
		}
		
		if (keyChange && i)
			xdo_send_keysequence_window_down(system, CURRENTWINDOW, keyMap[i], 0);
		else if (keyChange)
			xdo_send_keysequence_window_up(system, CURRENTWINDOW, keyMap[i], 0);
	}
}
