#include <DigiJoystick.h>
#include "WiitarLib.h"

Guitar gt = Guitar();

void setup() 
{
  // Creating new Guitar object
  gt.initialize();
}

void loop() 
{
  // update Guitar
  gt.update();

  // Mapping joystick and whammy bar to axes
  DigiJoystick.setY((byte) gt.Joy_Y);
  DigiJoystick.setX((byte) gt.Joy_X);
  DigiJoystick.setSLIDER((byte) gt.WhammyBar);
  
  // Minus (starpower button) is mapped to an axis because the DigiJoystick only supports 8 buttons. 
  // Works fine though..
  if(gt.Minus < 1)
  {
    DigiJoystick.setYROT((byte)255);
  }
  else
  {
    DigiJoystick.setYROT((byte)127);
  }
  
  // Initialize button byte
  int buttonByte = 0;
  
  // Write all buttons to this byte
  bitWrite(buttonByte, 0, !(byte)gt.Green);
  bitWrite(buttonByte, 1, !(byte)gt.Red);
  bitWrite(buttonByte, 2, !(byte)gt.Yellow);
  bitWrite(buttonByte, 3, !(byte)gt.Blue);
  bitWrite(buttonByte, 4, !(byte)gt.Orange);
  bitWrite(buttonByte, 5, !(byte)gt.StrumUp);
  bitWrite(buttonByte, 6, !(byte)gt.StrumDown);
  bitWrite(buttonByte, 7, !(byte)gt.Plus);

  // Map buttons
  DigiJoystick.setButtons((byte) buttonByte, (byte) 0);

  // Delay makes sure we actually communicate with the pc
  DigiJoystick.delay(1); 
}
