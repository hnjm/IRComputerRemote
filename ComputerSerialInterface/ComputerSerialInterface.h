#ifndef BARCODEREADER_H_
#define BARCODEREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

class SerialInterface
{
  public:
    SerialInterface() = default;
    ~SerialInterface() = default;
  private:
    int barCode = -1;
    int fileDescriptor = -1;
    char tty[1024] = "/dev/ttyACM0";

  private:
    void CleanBuffer();
  public:
    int Init();
    int ReadBarCode(char *_barCode, int _length);
    int Write(char *_buffer, int _length);
};

#endif // BARCODEREADER_H_
