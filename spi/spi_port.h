#ifndef _spi_port_h 
#define _spi_port_h

class spi_device; // Forward declaration for spi_device class.
class gpio;       // Forward declaration for gpio class.
struct spi_ioc_transfer;

class spi_port
{
	public:
		spi_port(int spiFile, int spiDriver=1);
		~spi_port();
    bool doIOwn(spi_device *curiousDevice);
    void takeOwnership(spi_device *bossyDevice);
		void transferData(spi_ioc_transfer *xfer);

	private:
		void configurePort();
		void configurePins(int spiDriver); 

		int _spiFile;   // Will be a file pointer to the SPI device.
		spi_device *_portOwner;
		gpio *_MOSI;
		gpio *_MISO;
		gpio *_SCK;
		gpio *_CS;
};

#endif

