#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "../gpio/gpio.h"
#include "spi_device.h"
#include "spi_port.h"

spi_device *_portOwner = NULL;

spi_port::~spi_port()
{
	close(_spiFile);
}

spi_port::spi_port(int spiFile, int spiDriver)
									 
{
	_spiFile = spiFile;
  _portOwner = NULL;
	configurePins(spiDriver);
}

void spi_port::configurePins(int spiDriver)
{
	if (spiDriver == 0)
	{
		_MOSI = new gpio(11, SPIPIN);
		_MISO = new gpio(12, SPIPIN);
		_SCK = new gpio(13, SPIPIN);
		_CS = new gpio (10, SPIPIN, HIGH);
	}
	else if (spiDriver == 2)
	{
		_MOSI = new gpio(21, SPIPIN);
		_MISO = new gpio(22, SPIPIN);
		_SCK = new gpio(23, SPIPIN);
		_CS = new gpio(20, SPIPIN, HIGH);
	}
}

// configurePort() only handles the parts which must be handled apart from
//  the message struct.
void spi_port::configurePort()
{
	if (_portOwner == NULL)
	{
		return;
	}
	// Set up the CS pin for the operation. We'll (naively) assume that the user
	//  hasn't done anything to the mode of the pins since we made them SPI pins,
	//  but we *do* need to worry about CS. If the owner of the port has a 
	//  non-standard CS pin, we need to use that one. Otherwise, we should use
	//  the default. Note that the NO_CS_PIN argument in the spi_ioc_transfer
	//  struct doesn't work with this library.
	if (!_portOwner->customCS())
	{
		_CS->mode(SPIPIN);
	}
	else
	{
    _CS->pinWrite(HIGH);
    _CS->mode(OUTPUT);
	}

	// We'll make a little temp variable to transmit the various mode info to 
	//  the SPI driver.
	int temp = 0;
  
	// The boolean lsbfirst is a rare case where the bit order should be 
	//  reversed during transmission; it corresponds to the SPI_LSB_FIRST
	//  constant in the spidev.h file.
 	if (_portOwner->doLSBFirst()) 
	{
		temp = SPI_LSB_FIRST;
		ioctl(_spiFile, SPI_IOC_WR_LSB_FIRST, &temp);
	}
	else
  {	
    temp = 0;
		ioctl(_spiFile, SPI_IOC_WR_LSB_FIRST, &temp);
	}

  temp = _portOwner->getSPIMode();
	ioctl(_spiFile, SPI_IOC_WR_MODE, &temp);
}

void spi_port::transferData(spi_ioc_transfer *xfer)
{
	if (_portOwner->customCS())
	{
		_portOwner->CSLow();
	}
	ioctl(_spiFile, SPI_IOC_MESSAGE(1), xfer);
	if (_portOwner->customCS())
	{
		_portOwner->CSHigh();
	}
}

bool spi_port::doIOwn(spi_device *curiousDevice)
{
  return (curiousDevice == _portOwner);
} 

void spi_port::takeOwnership(spi_device *bossyDevice)
{
  _portOwner = bossyDevice;
  configurePort();
}

