#ifndef _i2c_port_h
#define _i2c_port_h

class i2c_port
{
  public:
    i2c_port(int portFD, int portID);
    ~i2c_port();
    void takeOwnership(i2c_device *bossyDevice);
    bool doIOwn(i2c_device *curiousDevice);
    void writeBytes(int regAddr, unsigned char *buffer, int len);
    void readBytes(int regAddr, unsigned char *buffer, int len);
  private:
    i2c_device *portOwner;
    int _portFD;
    int _portID;
}
