#include <wiringPi.h>
#include <ads1115.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) 
{
  
	int16_t value;
  
	double voltage;

	ads1115Setup(100,0x48);

	for (;;) 
	{
    
		value = (int16_t) analogRead(100);
    
		voltage = value * (4.096 / 32768);
		
		printf("ADS1115 Reading: %d\n\r",value);
    
		printf("ADS1115 Voltage: %g\n\r",voltage);

		delay(1000);
  
	} 
	return 0;
}

