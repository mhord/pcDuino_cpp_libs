#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include "../gpio/gpio.h"

i2c_device *_portOwner = NULL;

i2c_port::~i2c_port()
{
	close(_portFD);
}

i2c_port::i2c_port(int portFD, int spiDriver)
{
	_portFD = portFD;
  _portOwner = NULL;
	configurePins();
}

void i2c_port::configurePins()
{
	if (_portID == 0)
	{
		_SDA = new gpio(11, SPIPIN);
		_SCL = new gpio(12, SPIPIN);
	}
	else if (_portID == 2)
	{
		_SDA = new gpio(11, SPIPIN);
		_SCL = new gpio(12, SPIPIN);
	}
}

// configurePort() only handles the parts which must be handled apart from
//  the message struct.
void i2c_port::configurePort()
{
}

void writeBytes(unsigned char *buffer, int len)
{
}

void readBytes(unsigned char *buffer, int len)
{
}

bool i2c_port::doIOwn(i2c_device *curiousDevice)
{
  return (curiousDevice == _portOwner);
} 

void i2c_port::takeOwnership(i2c_device *bossyDevice)
{
  _portOwner = bossyDevice;
  configurePort();
}

