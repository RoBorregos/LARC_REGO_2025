#ifndef INSTRUCTION_HANDLER_H
#define INSTRUCTION_HANDLER_H

#include <Arduino.h>

enum Function {
  NONE = 0,
  GETCOLOR = 1,
  GETCENTEROFFSETX = 2,
  GETCENTEROFFSETY = 3,
  GETOBJECTAREA = 4
};

class InstructionHandler {
private:
  uint8_t i2cAddress;
  String receivedMessage;
  bool messageReady = false;
  Function currentFunction = GETCOLOR;

public:
  InstructionHandler(uint8_t address);
  void begin();
  void update();

private:
  static void onReceiveWrapper(int numBytes);
  static void onRequestWrapper();
  void onReceive(int numBytes);
  void onRequest();
};

#endif // INSTRUCTION_HANDLER_H