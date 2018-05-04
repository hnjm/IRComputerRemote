#include "SerialInterface.h"

int SerialInterface::Init() {
  std::cout << tty << std::endl;
  // Open the file descriptor in non-blocking mode
  fileDescriptor = open(tty, O_RDWR | O_NOCTTY);
  if (fileDescriptor < 0) {
    std::cout << "Failed to open barcode reader port on " << tty << std::endl;
    return -1;
  }

  struct termios toptions; // Set up the control structure

  tcgetattr(fileDescriptor, &toptions); // Get currently set options for the tty

  // Set custom options
  // 115200 baud
  cfsetispeed(&toptions, B115200);

  // 8 bits, no parity, no stop bits
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  // no hardware flow control
  toptions.c_cflag &= ~CRTSCTS;
  // enable receiver, ignore status lines
  toptions.c_cflag |= CREAD | CLOCAL;
  // disable input/output flow control, disable restart chars
  toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
  // disable canonical input, disable echo,
  // disable visually erase chars,
  // disable terminal-generated signals
  toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  // disable output processing
  toptions.c_oflag &= ~OPOST;

  // wait for 12 characters to come in before read returns
  // WARNING! THIS CAUSES THE read() TO BLOCK UNTIL ALL
  // CHARACTERS HAVE COME IN!
  toptions.c_cc[VMIN] = 0; // 0 => set read function not blocking
  // no minimum time to wait before read returns
  toptions.c_cc[VTIME] = 0; // 0 => set read function not blocking

  // Commit the options
  tcsetattr(fileDescriptor, TCSANOW, &toptions);

  CleanBuffer();

  return 0;
}

void SerialInterface::CleanBuffer(){
  // Flush anything already in the serial buffer
  tcflush(fileDescriptor, TCIFLUSH);
}

int SerialInterface::Write(char* _buffer, int _length) {
  std::cout << "Write " << _buffer << std::endl;
  return write(fileDescriptor, _buffer, _length);
}

int SerialInterface::ReadBarCode(char *_buffer, int _length){
  return read(fileDescriptor, _buffer, _length);
}
