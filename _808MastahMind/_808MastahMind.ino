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
 flash DimGreen and FullOn. If you don't guess the secret code in eight tries, the secret code will be displayed in the
 evaluation area and pressing the "B" button will reset the game but save your score.
 
 The scoring system operates by a point system, plus one point for winning
 and minus on point for losing. You may not have less than 0 points. One you have a total
 of eight points you win the game.
 
 Once you "Win" with a total of eight points, restart the game by turning the power
button off and on. 
 
 
 ////////////////////////////////////////////////////////////////////////////////////
 The Program Starts Here
 IMPORTANT NOTE:
 Resources Used:
 http://arduino.cc/en/Reference/HomePage
 http://www.evilmadscientist.com/
 Both of these websites were essential to my code. I used arduino to understand
 the code that I revieved. A sizable portion of this code is directly from
 the evilmadscientist library. The part of the code that I tweeked and worked 
 on were the scoring system, the win screen and the directional controls.
 For the most part I studied the code to figure out what it was doing and then I 
 commented what exactly its function was. See write up.
*/ 
#include <MeggyJrSimple.h>    
#define maxColor 2 // highest numbered color in range
#define minColor 1 //lowest number color in range

int cursorX = 0; //x axis controlling variable
int guessY = 0;//yaxis controlling vairable
int score = 0;
int prevColor;
int colorChoice;
int secretCode[4]; //Generated code the player has to guess
int guessCode[4]; // the submitted guess of the player
boolean reset; //Allows for the true and false boolean to play muiltiple times
void setup()   // after each round of eight guesses                
{

  MeggyJrSimpleSetup();   
  score=0; //beggining score, no points, no lights
  } 
  void Win() //The Letters for Winning, must achieve a score of 8 for it to play
{
  ClearSlate();//The letter W 
  DrawPx(1,6,random);
  DrawPx(1,5,4);
  DrawPx(1,4,4);
  DrawPx(1,3,4);
  DrawPx(1,2,random);
  DrawPx(1,1,4);
  DrawPx(2,1,4);
  DrawPx(3,1,4);
  DrawPx(3,2,random);
  DrawPx(3,3,4);
  DrawPx(3,4,4);
  DrawPx(4,4,4);
  DrawPx(4,3,4);
  DrawPx(4,2,random);
  DrawPx(4,1,4);
  DrawPx(5,1,4);
  DrawPx(6,1,random);
  DrawPx(6,2,4);
  DrawPx(6,3,4);
  DrawPx(6,4,random);
  DrawPx(6,5,4);
  DrawPx(6,6,random);
  DisplaySlate();
  delay(500);
  ClearSlate();
  Tone_Start(ToneC5, 50);
  DrawPx(3,0,4);//the letter I
  DrawPx(3,1,4);
  DrawPx(3,2,4);
  DrawPx(3,3,4);
  DrawPx(3,4,4);
  DrawPx(4,1,4);
  DrawPx(4,0,4);
  DrawPx(4,2,4);
  DrawPx(4,3,4);
  DrawPx(4,4,4);
  DrawPx(3,6,random);
  DrawPx(3,7,random);
  DrawPx(4,6,random);
  DrawPx(4,7,random);
  DisplaySlate();
  delay(500);
  ClearSlate();
  ClearSlate();
  DrawPx(1,6,random);//the leter N
  DrawPx(1,5,4);
  DrawPx(1,4,random);
  DrawPx(1,3,4);
  DrawPx(1,2,random);
  DrawPx(1,1,4);
  DrawPx(2,5,random);
  DrawPx(3,4,4);
  DrawPx(4,3,4);
  DrawPx(5,2,random);
  DrawPx(6,1,4);
  DrawPx(6,2,4);
  DrawPx(6,3,random);
  DrawPx(6,4,4);
  DrawPx(6,5,random);
  DrawPx(6,6,4);
  DisplaySlate();
  delay(500);
  ClearSlate();
  Tone_Start(ToneC5, 50);

}
// This portion down is code directly from a form of the game I found.
void blinkCursor(){ //causes the selected space, the cursor area to blink for the players conveinence
  prevColor=ReadPx(cursorX,guessY); 
  DrawPx(cursorX,guessY,FullOn); // causes the full on to act as a "blink" or blight flash
  DisplaySlate();
  delay(9);
  DrawPx(cursorX,guessY,prevColor); //causes the blink in the space with current color
  DisplaySlate();
  delay(180);
}

void setGuessCode(){  //Creates a GuessCode Array
 if (guessY == 0) {   
  for (int i=0;i<4;i++){
    guessCode[i]=minColor; //makes the first row the minColor
    DrawPx(i,guessY,minColor); //draws red as the first code
  }
 }
 else {
   for (int i=0;i<4;i++) { //copy previous guess in the subsequent row
     guessCode[i]=ReadPx(i,guessY-1); //displays the previous y axis slot as the lower row
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
  for (int i=0;i<4;i++){ 
    secretCode[i]=random(minColor,maxColor+1); //creates random secret code from anything between or equal
  }                                            // the minimum or maximum color, created by game
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
    if (Button_A)  { //Listed under thier library
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
      if (correct>0){ 
        for (int i=0; i<correct;i++){
          DrawPx(position,guessY,FullOn);
          position++;
        } 
       DisplaySlate(); //I edited this scoring system bellow from the one found on the code
                       //so that it fits my idea of the game 
      }
     if (correct==4){ // If the Player Wins
       while (!Button_B){ //Makes it so that only when the game ends the B button reset works.
        CheckButtonsDown();
        for (int i=4;i<8;i++){
          DrawPx(i,guessY,FullOn); //flashses full on on the guess side of the board
        }
        DisplaySlate();//flashes the dimgreen on the guess side of the board, alternated with fullon
        delay(20);
        for (int i=4;i<8;i++){ //makes it so that only the last four dots blink
          DrawPx(i,guessY,DimGreen); //keeps the blinking to the the correct guessed line
        }
        DisplaySlate();
        delay(200);
       }
       score=score+1; //Adds plus one to the LED lights, adds one to the score
       reset=true;
      }
     else {
      if (guessY == 7) { //If the Player loses
        for (int i=4;i<8;i++){
          DrawPx(i,guessY,secretCode[i-4]); //Show what the secret code was
        }
        DisplaySlate();
        while (!Button_B){
          CheckButtonsDown();
        }
        score=score - 1; // takes away, meaning turns off,  an LED light when you fail to guess
        reset=true;//      the answer after eight tries
      }
      if (correctColorOnly>0){
        for (int i=0; i<correctColorOnly;i++){ 
          DrawPx(position,guessY,DimGreen); // if its only the correct color make it dim green
          position++;
        }
        
      } 
      
      else { //created this part and edited to the other scoring portions to make it
        if (score == 8) { // so that this part means you have to obtain a score of
          ClearSlate; // eight for the winning animation to show
          Win();
         //edited scoring ends here
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
        cursorX--; //keeps the cursor within the first four x axis slots
      }
      DisplaySlate();
    }
    if (Button_Right){
      if (cursorX == 3) {
        cursorX = 0;
      }
      else {
        cursorX++; //keeps the cursor within the first four x axis slots
      }
      DisplaySlate();
    }                     
    if (Button_Up) {//allows for the player to swap through color
      colorChoice=ReadPx(cursorX,guessY);
      if (colorChoice == maxColor) {
        DrawPx(cursorX,guessY,minColor);
      }
      else {
        colorChoice++;
        DrawPx(cursorX,guessY,colorChoice); //sets the limits for the colors that can be picked
      }
      DisplaySlate();

    }
    if (Button_Down) {//allows for the player to swap through colors
      colorChoice=ReadPx(cursorX,guessY);
      if (colorChoice == minColor) {
        DrawPx(cursorX,guessY,maxColor); //sets the limits for the colors that can be picked
      }
      else {
        colorChoice--;
        DrawPx(cursorX,guessY,colorChoice);
      }
      DisplaySlate();
/*void selector() // note alternative program that I wrote for the directional movement
                   took this out of the game because there was a glitch when the win
                   screen was displayed that a full on dot could be moved and switched on
                   and off. Kinda creepy didn't work out well.                
{
  CheckButtonsDown();
  if (Button_Right)
      {
        if (cursorX < 4)
        cursorX = cursorX + 1;
      } 
    if (Button_Left)
      {
        if (cursorX > 0)
        cursorX = cursorX - 1;
      }
      if(Button_A&&Button_B){ //resets the game but saves score
      reset=true;
   }
}
*/
    }
    blinkCursor(); //causes the cursor to blink indicating which dot is currently
                  // being selected by the player for changing
  }  
}
/*
Pseudo Code Project plan
1. Movement controls for the dot, isolation of movement so that the guess and the 
guess indicator are seperate.
2.Create a code generator which can run independently from a given pattern
3.Program indicators for whether or not the guess is correct
4. create a boolean for the win and lose, create a parameter for what is scoring
5. Learn how to work and integrate the LED system
*/
