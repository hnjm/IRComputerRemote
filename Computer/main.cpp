#include "SerialInterface.h"
#define BUFFERSIZE 512

int main() {
  char buffer[BUFFERSIZE];
  SerialInterface serialInterface;
  serialInterface.Init();
  sleep(3);
 
  for (int i=0; i<10; i++) {
    // Read message received from Arduino
    if (serialInterface.ReadBarCode(buffer, BUFFERSIZE ) > 0 ) {
      std::cout << "Msg from Arduino: " << buffer << std::endl;
    } else {
      std::cout << "No data" << std::endl;
    }

    // Send command to Arduino via serial interface
    if (serialInterface.Write("0", 3) < 0)
      std::cout << "ERROR - Function Write failed" << std::endl;

    std::cout << "Loop " << i << std::endl;
    sleep(1);
  }
}
