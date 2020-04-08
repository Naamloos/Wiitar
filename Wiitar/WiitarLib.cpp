#include <TinyWireM.h>
#include "WiitarLib.h"

void Guitar::initialize()
{
  // Open connection
  TinyWireM.begin();

  // Handshaking
  TinyWireM.beginTransmission(0x52);
  TinyWireM.send(0xF0);
  TinyWireM.send(0x55);
  TinyWireM.endTransmission();
  delay(1);
  TinyWireM.beginTransmission(0x52);
  TinyWireM.send(0xFB);
  TinyWireM.send(0x01);
  TinyWireM.send(byte(0x00));
  TinyWireM.endTransmission();
}

void Guitar::update()
{
  byte resp[6]; // Response byte array

  // Request new data
  TinyWireM.requestFrom(0x52, 6);

  // Fetch new data
  int i = 0;
  while(TinyWireM.available())
  {
    resp[i] = TinyWireM.receive();
    i++;
  }

  // Mapping all data to object.
  // These are just axes
  Guitar::Joy_X = map(resp[0], 0, 64, -15, 271);
  Guitar::Joy_Y = map(resp[1], 0, 64, -15, 271);
  Guitar::WhammyBar = map(resp[3], 220, 255, 0, 256);

  // Buttons
  Guitar::StrumUp = (resp[5] >> 0) & 1;
  Guitar::StrumDown = (resp[4] >> 6) & 1;
  Guitar::Minus = (resp[4] >> 4) & 1;
  Guitar::Plus = (resp[4] >> 2) & 1;
  Guitar::Green = (resp[5] >> 4) & 1;
  Guitar::Red = (resp[5] >> 6) & 1;
  Guitar::Yellow = (resp[5] >> 3) & 1;
  Guitar::Blue = (resp[5] >> 5) & 1;
  Guitar::Orange = (resp[5] >> 7) & 1;

  // Tell guitar we're ready for the next input
  TinyWireM.beginTransmission(0x52);
  TinyWireM.send(byte(0x00));
  TinyWireM.endTransmission();
}
