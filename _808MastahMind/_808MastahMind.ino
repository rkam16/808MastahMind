/*
808Mastah_Mind.pde
 
 OBJECT OF GAME:
 Match the secret code sequence of 4 colors in 8 or fewer guesses and get
 points and another chance to play!
 
 GAME CONTROLS:
 <LEFT> Moves cursor left.
 <RIGHT> Moves cursor right.
 <UP> cycles up through colors.
 <DOWN> cycles down through colors.
 
 <Button_A> Submits guess for evaluation.
 <Button_B> Starts next game. Resets only once you have used all eight guesses
 
 Push A & B Together quickly to reset the game. Works even if you haven't
 used all eight of your guesses.
 
 GAME PLAY:
 Move blinking cursor with left and right buttons to select pixel to change.
 Use up and down buttons to cycle through colors. Push Button "A" to have Meggy
 evaluate your guess. 
 
 FullOn pixels mean position and color are both correct.
 DimGreen mean a color is correct, but it is in the wrong position.
 If there is no light on then none of the guesses are correct.
 
 The DimGreen and FullOn DO NOT indicate which of the guess colors are correct,
 you must figure that out for yourself. Each light will only indicate that a guess is
 either the correct color and/or the correct space. 
 
 WINNING THE GAME:
 Match the secret code sequence of four colors correctly the four evaluation pixles will
 flash DimGreen and FullOn. The fewer the guesses, the higher the score. You can get a total
 of eight lights on, the more lights you have the less guesses were used.
 
 If you don't guess the secret code in eight tries, the secret code will be displayed in the
 evaluation area and pressing the "B" button will reset the game and your score.
 
 
 ////////////////////////////////////////////////////////////////////////////////////
 The Program Starts Here
 Resources Used http://arduino.cc/en/Reference/HomePage
 http://www.evilmadscientist.com/
 Both of these websites provided the foundation for the Guess and the 
 recognition function for my game. Only one part of this code is nearly
 identicle to a code found on line, area is commented.
 Other than that most things are original and based off of lessons that
 are taught on the arduino.cc website.
*/ 
#include <MeggyJrSimple.h>    

#define maxColor 4 // highest numbered color in range
#define minColor 1 //lowest number color in range
byte prevColor, score, cursorX,guessY,colorChoice,secretCode[4],guessCode[4];
boolean reset;

void setup()                    
{

  MeggyJrSimpleSetup();   
  score=0;
  } 

void blinkCursor(){
  prevColor=ReadPx(cursorX,guessY);
  DrawPx(cursorX,guessY,FullOn);
  DisplaySlate();
  delay(9);
  DrawPx(cursorX,guessY,prevColor);
  DisplaySlate();
  delay(180);
}

void setGuessCode(){  //Creates a GuessCode Array
 if (guessY == 0) {   //makes the first row the minColor
  for (int i=0;i<4;i++){
    guessCode[i]=minColor;
    DrawPx(i,guessY,minColor);
  }
 }
 else {
   for (int i=0;i<4;i++) { //copy previous guess in the subsequent row
     guessCode[i]=ReadPx(i,guessY-1);
     DrawPx(i,guessY,guessCode[i]);
   }
   DisplaySlate();
 }
}
  

void loop()                   
{  
  ClearSlate();
  SetAuxLEDs(score);
  cursorX=0; //cursor x-axis position
  guessY=0; //cursor y-axis position increments with each player guess
  colorChoice=1;
  for (int i=0;i<4;i++){ //creates random secret code
    secretCode[i]=random(minColor,maxColor+1);
  }
  setGuessCode(); //makes guessCode array to an appropriate condition
  DisplaySlate();
  reset = false;  
  while (!reset) { 

    CheckButtonsPress();  

    if(Button_A&&Button_B){ //resets the game but saves score
      reset=true;
      }
    

    // Evaluate the player's guess
    // Found this part of the reading Code Online from the Evil Made Genius Website.http://www.evilmadscientist.com/
    if (Button_A)  { 
      byte correct = 0;
      byte correctColorOnly = 0;
      byte position = 4;
      boolean secretCodeMatched[4],guessCodeMatched[4];
      for (int i=0;i<4;i++){ 
        guessCodeMatched[i]=false;
        secretCodeMatched[i]=false;
      }
      for(int i=0; i<4; i++){ 
        guessCode[i]=ReadPx(i,guessY);//reads the players guess
      }
      for (int i=0; i<4; i++){ //Count guesses that are correct in color and position
        if (guessCode[i]==secretCode[i]){
          secretCodeMatched[i]=true;
          guessCodeMatched[i]=true;  //so we don't count them again
          correct++;
        }
      }
      for (int i=0; i<4; i++){ //Count guesses that are correct colors in wrong positions
          if (!guessCodeMatched[i]){
            for (int j=0; j<4; j++){
              if (!secretCodeMatched[j]){
                if(guessCode[i]==secretCode[j]){
                   secretCodeMatched[j]=true;
                   correctColorOnly++;
                   break; //so we count matches only once
                  }
                }
            }
          }
          
      }
      //The Copied part of the code ends here.
      if (correct>0){ 
        for (int i=0; i<correct;i++){
          DrawPx(position,guessY,FullOn);
          position++;
        }
       DisplaySlate();
      }
     if (correct==4){ // If the Player Wins
       while (!Button_B){ //Makes it so that only when the game ends the B button reset works.
        CheckButtonsDown();
        for (int i=4;i<8;i++){
          DrawPx(i,guessY,FullOn);
        }
        DisplaySlate();
        delay(20);
        for (int i=4;i<8;i++){
          DrawPx(i,guessY,DimGreen);
        }
        DisplaySlate();
        delay(200);
       }
       score=score+8-guessY; //Score can be 1-8 depening on hte # of Guesses used
       reset=true;
      }
     else {
      if (guessY == 7) { //If the PLayer loses
        for (int i=4;i<8;i++){
          DrawPx(i,guessY,secretCode[i-4]); //Show what the secret code was
        }
        DisplaySlate();
        while (!Button_B){
          CheckButtonsDown();
        }
        score=0;
        reset=true;
      }
      if (correctColorOnly>0){
        for (int i=0; i<correctColorOnly;i++){
          DrawPx(position,guessY,DimGreen);
          position++;
        }
        
      } 
      
      guessY++; //move up a row for the next guess
      setGuessCode();
      cursorX=0;
      DisplaySlate(); 
     }
    }
    if (Button_Left){
      if (cursorX == 0) {
        cursorX=3;
      }
      else {
        cursorX--;
      }
      DisplaySlate();
    }
    if (Button_Right){
      if (cursorX == 3) {
        cursorX = 0;
      }
      else {
        cursorX++;
      }
      DisplaySlate();
    }                     
    if (Button_Up) {
      colorChoice=ReadPx(cursorX,guessY);
      if (colorChoice == maxColor) {
        DrawPx(cursorX,guessY,minColor);
      }
      else {
        colorChoice++;
        DrawPx(cursorX,guessY,colorChoice);
      }
      DisplaySlate();

    }
    if (Button_Down) {
      colorChoice=ReadPx(cursorX,guessY);
      if (colorChoice == minColor) {
        DrawPx(cursorX,guessY,maxColor);
      }
      else {
        colorChoice--;
        DrawPx(cursorX,guessY,colorChoice);
      }
      DisplaySlate();

    }
    blinkCursor();
  }  
}
