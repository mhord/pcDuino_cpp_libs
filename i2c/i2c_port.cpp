#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include "../gpio/gpio.h"
#include "i2c_port.h"

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
		_SDA = new gpio(18, I2CPIN);
		_SCL = new gpio(19, I2CPIN);
	}
	else if (_portID == 2)
	{
		_SDA = new gpio(11, I2CPIN);
		_SCL = new gpio(12, I2CPIN);
	}
}

// configurePort() only handles the parts which must be handled apart from
//  the message struct.
void i2c_port::configurePort()
{
}

void i2c_port::transferPackets(i2c_rdwr_ioctl_data *transactions)
{
  ioctl(_portFD, I2C_RDWR, transactions);
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

