#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include "i2c_port.h"
#include "../gpio/gpio.h"

int main()
{
  int portFD = open("/dev/i2c-1", O_RDWR);
  i2c_port myPort(portFD, 0);
  i2c_rdwr_ioctl_data transactions;
  i2c_msg messages[2];
  printf("%d\r\n", portFD);
  unsigned short mpr121Address = 0x005a;
  unsigned char regAddr = 0x5d;
  unsigned char *dBuf;
  messages[0].len = 1;
  messages[0].flags = 0;
  messages[0].addr = mpr121Address;
  messages[0].buf = &regAddr;

  messages[1].addr = mpr121Address;
  messages[1].flags = I2C_M_RD;
  messages[1].len = 1;
  messages[1].buf = dBuf; 
  
  transactions.nmsgs = 2;
  transactions.msgs = messages;

  myPort.transferPackets(&transactions);
  printf("%x\n\r", dBuf);

} 
