#ifndef __gpio_h__
#define __gpio_h__


// Make some aliases to make the code more readable.
#define HIGH '1'
#define LOW  '0'

#define INPUT  '0'
#define OUTPUT '1'
#define INPUT_PU '8'
#define SPIPIN '2'
#define SPIPIN2 '3'
#define I2CPIN '2'

class gpio
{
	public:
		gpio(int pinID, int initMode, int initVal=LOW);
		~gpio();
		void mode(int newMode);
		void pinWrite(int newLevel);
		int pinRead();

	private:
    gpio();
};

#endif

