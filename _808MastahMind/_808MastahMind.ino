/* 808Mastah Mind.pde
*/
#include <MeggyJrSimple.h> // Required code
#define maxColor 6 // highest numbered color in range
#define minColor 1 //lowest number color in range
byte prevColor,cursorX,guessY,score,colorChoice,secretCode,guessCode; 

int xcoord = 0;
int ycoord = 0;

void setup()               // required code 
  {
  MeggyJrSimpleSetup();
  score=0;  
  }

void blinkCursor()
  {
  prevColor=ReadPx(cursorX,guessY);
  DrawPx(cursorX,guessY,FullOn);
  DisplaySlate();
  delay(9);
  DrawPx(cursorX,guessY,prevColor);
  DisplaySlate();
  delay(180);
 }

void loop()
{  
void setGuessCode(){
if


