/* 808Mastah Mind.pde
*/
#include <MeggyJrSimple.h> // Required code

int xcoord = 0;
int ycoord = 0;

void setup()               // required code 
{
  MeggyJrSimpleSetup();  
}

void loop()
{
 
  CheckButtonsPress();
 
  
  
  if (Button_Right)
  {
    direction = 90;
  }
  
  if (Button_Left)
  {
    direction = 270;
  }
  
  if (Button_Up)
  {
   direction = 0; 
  }
  
  if (Button_Down)
  {
    direction = 180;
  }
}  
