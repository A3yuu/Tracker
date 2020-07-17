#include "network.h"

  void Network::begin(String name){
    SerialBT.begin(name);
  }
  void Network::send(String data){
    SerialBT.println(data);
  }
