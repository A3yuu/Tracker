#include "network.h"

Network network;

void setup() {
  network.begin("ESP32");
}

void loop() {
  network.send("Hello World");
  delay(1000);
}
