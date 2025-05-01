#include "InstructionHandler.h"
#include <Wire.h>

// Necesario para llamar métodos no estáticos desde static callbacks
InstructionHandler* instance = nullptr;

InstructionHandler::InstructionHandler(uint8_t address)
  : i2cAddress(address) {
  instance = this;
}

void InstructionHandler::begin() {
  Wire.begin(i2cAddress);
  Wire.onReceive(onReceiveWrapper);
  Wire.onRequest(onRequestWrapper);
}

void InstructionHandler::update() {
  // if (robot.detectsColor()) currentFunction = GETCOLOR; !gente de visión help
}

void InstructionHandler::onReceiveWrapper(int numBytes) {
  if (instance) instance->onReceive(numBytes);
}

void InstructionHandler::onRequestWrapper() {
  if (instance) instance->onRequest();
}

void InstructionHandler::onReceive(int numBytes) {
  receivedMessage = "";
  while (Wire.available()) {
    char c = Wire.read();
    receivedMessage += c;
  }

  receivedMessage.trim();

  if (receivedMessage == "GIVE_INSTRUCTION") {
    messageReady = true;
  }

  Serial.print("Received: ");
  Serial.println(receivedMessage);
}

void InstructionHandler::onRequest() {
  if (messageReady) {
    Wire.write(String(currentFunction).c_str());
    messageReady = false;
    Serial.print("Sent Function: ");
    Serial.println(currentFunction);
  } else {
    Wire.write("0");
  }
}