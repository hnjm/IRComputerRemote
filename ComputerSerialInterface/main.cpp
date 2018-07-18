#include "SerialInterface.h"

#define BUFFERSIZE 512

int main() {

  // Linux terminal command
  FILE *out;

  char buffer[BUFFERSIZE];
  SerialInterface serialInterface;
  serialInterface.Init();
  sleep(3);

  for (int i=0; i<10; i++) {
    // Read message received from Arduino, using IR remote
    if (serialInterface.ReadBarCode(buffer, BUFFERSIZE ) > 0 ) {
      std::cout << "Msg received from Arduino: " << buffer << std::endl;

      // Change Linux audio volume
      if ( (atoi(buffer) >= 0) && (atoi(buffer) <= 100)) {
        std::cout << "Change volume to " << atoi(buffer) << std::endl;
        char terminalCmd[1024] = "";
        snprintf(terminalCmd, sizeof(terminalCmd), "amixer sset 'Master' %d%", atoi(buffer));
        if ( (out = popen (terminalCmd, "r")) == NULL)
           std::cout << "ERROR when trying to change audio volume" << std::endl;
       }
    } else {
      std::cout << "No data from Arduino" << std::endl;
    }

    // Send command to Arduino via serial interface
    char cmdToArduino[512] = "0";
    if (serialInterface.Write(cmdToArduino, 3) < 0)
      std::cout << "ERROR - Function Write failed" << std::endl;

    sleep(1);
  }
}
