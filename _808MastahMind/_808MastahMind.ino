/* 808Mastah Mind.pde
*/
#include <MeggyJrSimple.h> // Required code
#define maxColor 6 // highest numbered color in range
#define minColor 1 //lowest number color in range
byte prevColor, score, cursorX,guessY,colorChoice,secretCode[4],guessCode[4];
boolean reset;

void setup()                    // run once, when the sketch starts
{

  MeggyJrSimpleSetup();   // Required code, line 2 of 2.
  score=0;
  } // End setup()

void blinkCursor(){
  prevColor=ReadPx(cursorX,guessY);
  DrawPx(cursorX,guessY,FullOn);
  DisplaySlate();
  delay(9);
  DrawPx(cursorX,guessY,prevColor);
  DisplaySlate();
  delay(180);
}

void setGuessCode(){  //initialize guessCode array
 if (guessY == 0) {   //if first row set to minColor
  for (int i=0;i<4;i++){
    guessCode[i]=minColor;
    DrawPx(i,guessY,minColor);
  }
 }
} 

void loop()                     
{  
 //Intial Conditions 
  ClearSlate();
  SetAuxLEDs(score);
  cursorX=0; 
  guessY=0; 
  colorChoice=1;
  for (int i=0;i<4;i++){ 
    secretCode[i]=random(minColor,maxColor+1);
  }
  setGuessCode(); 
  DisplaySlate();
  reset = false;  
  while (!reset){ 

    CheckButtonsPress();   

    if(Button_A&&Button_B){ //reset the game, have to hit both buttons
      reset=true;
      }
    
    if (Button_A) {
    byte correct = 0;  
    byte correctColorOnly = 0;
    byte position = 4;
    boolean secretCodeMatched[4],guessCodeMatched[4];
    for (int i=0;i<4;i++){ 
    guessCodeMatched[i]=false;
    secretCodeMatched[i]=false;
    }
    for(int i=0; i<4; i++){ 
        guessCode[i]=ReadPx(i,guessY);//read the Player's gu7ess into an array
      }
      for (int i=0; i<4; i++){ //Count guesses that are correct in color and position
        if (guessCode[i]==secretCode[i]){
        secretCodeMatched[i]=true;
        guessCodeMatched[i]=true;  //so it don't  count them again
        correct++;
      }
     } 
