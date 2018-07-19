#include "SerialInterface.h"

#define BUFFERSIZE 512
#define DELAY_SEC 1

static bool SetAudioVolume(const int _volumePercent) {
  FILE *ioStream;
  if ( (_volumePercent <= 0) && (_volumePercent >= 100)) {
    std::cout << "ERROR, volume must be between 0 and 100%" << std::endl;
    return false;
  }

  std::cout << "Change volume to " << _volumePercent << std::endl;
  
  char terminalCmd[BUFFERSIZE] = "";
  snprintf(terminalCmd, sizeof(terminalCmd), "amixer sset 'Master' %d%", _volumePercent);
  if ( (ioStream = popen (terminalCmd, "r")) == NULL) {
    std::cout << "ERROR when trying to change audio volume" << std::endl;
    return false;
  }

  pclose(ioStream);

  return true;
}

int main() {
  char buffer[BUFFERSIZE];
  
  std::string TTY = "/dev/ttyACM0";
  SerialInterface serialInterface;
  serialInterface.Init(TTY);
  sleep(3);

  char keyboardEntry;
  while (keyboardEntry != 'q') {
    // Read message received fom Arduino via serial interface
    if (serialInterface.Read(buffer, BUFFERSIZE ) > 0 ) {
      std::cout << "Msg received from Arduino: " << buffer << std::endl;

      // Change Linux audio volume
      if(SetAudioVolume(atoi(buffer)) == false)
        std::cout << "ERROR, failed to set computer audio volume " << std::endl;

    }

    // Send command to Arduino via serial interface
    char cmdToArduino[BUFFERSIZE] = "0";
    if (serialInterface.Write(cmdToArduino, 3) < 0)
      std::cout << "ERROR - Function Write failed" << std::endl;

    std::cin >> keyboardEntry;
    sleep(DELAY_SEC);
  }
}
