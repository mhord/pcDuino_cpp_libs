#ifndef _i2c_port_h
#define _i2c_port_h

class i2c_device;
class gpio;

class i2c_port
{
  public:
    i2c_port(int portFD, int portID);
    ~i2c_port();
    void takeOwnership(i2c_device *bossyDevice);
    bool doIOwn(i2c_device *curiousDevice);
    void transferPackets(i2c_rdwr_ioctl_data *transactions);
  private:
    i2c_device *_portOwner;
    int _portFD;
    int _portID;
    void configurePort();
    void configurePins();
    gpio *_SDA;
    gpio *_SCL;
};
#endif

