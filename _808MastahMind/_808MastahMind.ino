/* 808Mastah Mind.pde
*/
#include <MeggyJrSimple.h> // Required code

int xcoord = 0;
int ycoord = 0;

void setup()               // required code 
  {
  MeggyJrSimpleSetup();
  score=0;  
  }

void blinkCursor()
  {
  prevColor=ReadPx(guessX,guessY);
  DrawPx(guessX,guessY,FullOn);
  DisplaySlate();
  delay(9);
  DrawPx(guessX,guessY,prevColor);
  DisplaySlate();
  delay(180);
 }

void loop()                     // run over and over again
{  
  ClearSlate();
  SetAuxLEDs(score);
  guessX=0; //
  guessY=0; //
  
}
  
 
