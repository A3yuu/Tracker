#include <BluetoothSerial.h>

class Network{
  BluetoothSerial SerialBT;
  public:
  void begin(String name);
  void send(String data);
};
