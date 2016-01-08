#include "io-scan/io-scan.h"

// A simple example that reads an analog moisture sensor and turns on a buzzer if the 
// moisture level reading exceeds a threshold.  An input pushbutton can silence the buzzer when pressed.

#define	QUIET_BUTTON_PIN			D3
#define	BUZZER_PIN					D4
#define	MOISTURE_SENSOR_PIN		A0

DigitalInput		quiet_button(QUIET_BUTTON_PIN);
DigitalOutput		buzzer(BUZZER_PIN);
AnalogInput			moisture_sensor(MOISTURE_SENSOR_PIN);

int					scan_timer_ms				= 0;
bool					buzzer_silenced			= false;

void setup 
{
   buzzer.Off();
   scan_timer_ms  = millis();
}


void loop 
{
	// Scan the silence button every 10mS in order to debounce.

   if ((millis() - scan_timer_ms) > 10)
   {
      quiet_button.Scan();

		// RisingEdge is valid for one scan on a transition.

		if (quiet_button.RisingEdge())
		{
			buzzer_silenced	= true;
		}
		
		scan_timer_ms	= millis();
	}

	if (moisture_sensor.ReadVoltage() > 1.5)
	{
		if (!buzzer_silenced)
		{
			buzzer.On();
		}
		else
		{
			buzzer.Off();
		}
	}
	else
	{
		buzzer_silenced	= false;					// Re-enable the buzzer
		buzzer.Off();
	}
}
