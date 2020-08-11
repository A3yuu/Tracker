#include <BluetoothSerial.h>
#include "network.h"

  BluetoothSerial SerialBT;
  
  void Network::begin(String name){
    SerialBT.begin(name);
  }
  void Network::send(String data){
    SerialBT.println(data);
  }
