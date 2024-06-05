#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay Adelaytime;
//the pin number for the buttons and slideswitch
const byte slideswitchpin = 7;
const byte rightbuttonpin = 5;
const byte leftbuttonpin = 4;

/*
//----tone conversion on midi scale----
float midi[127];
int A_four = 440; // a is 440 hz...
*/

int difficultylevel = 0;
bool startvar = 0;

//------------------ISR affected variables----------------------
volatile bool Switchflag = 0;
volatile bool rightbuttonflag = false;
volatile bool leftbuttonflag = false;

//---------------
bool RightAns = 0;
bool WrongAns = 0;
int Score = 0;
int diffchange = 0;


//int Delaytime[6] = {3500, 3000, 2500, 2000, 1500, 1000};

//-----------------------------------setup---------------------------------
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  //Adelaytime.start(3000, AsyncDelay::MILLIS);//use in the switch case
  attachInterrupt(digitalPinToInterrupt(slideswitchpin), switchISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightbuttonpin), rightbuttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(leftbuttonpin), leftbuttonISR, FALLING);
  //generateMIDI(); // Custom function for calculating and storing the frequency value associated for each MIDI pitch number
}

//------------------------------------main--------------------------------------------
void loop() {
Serial.print("current difficulty");
Serial.println(difficultylevel);
Serial.print("startval");
Serial.println(startvar);

/* //switched to using interupts
rightbutton = CircuitPlayground.rightButton();
leftbutton = CircuitPlayground.leftButton();
delay(100);
*/


  //--------limit the difficulty level----------
  if(difficultylevel > 6){
    difficultylevel = 6;
  }
  else if(difficultylevel<0){
    difficultylevel = 0;
  }


//----------------------------------gamecode start-up---------------------------------------------
if(!startvar){//the before game difficulty set up loop
  if(rightbuttonflag){
    delay(20);
    difficultylevel++;
    rightbuttonflag = 0;
    CircuitPlayground.playTone(600,20);
    CircuitPlayground.playTone(400,20);//set first value between 350-450
    CircuitPlayground.playTone(600,20);
  }
  if(leftbuttonflag){
    delay(20);
    difficultylevel--;
    leftbuttonflag = 0;
    CircuitPlayground.playTone(550,20);
    CircuitPlayground.playTone(400,20);//set first value between 350-450
    CircuitPlayground.playTone(550,20);
  }


  //the slideswitch code that triggeres the game start loop via interrupt so the interrupt can be reued
  if(Switchflag)
    startvar = 1;//only turn back to false when game over   
}





//-----------------------------------gamecode play-----------------------------
if(startvar){
  //random slect the case, then have the case have async delay start, at the end use is 
  //expired to tell when  time is up and add to the WrongAns variable
  //dificulty will set the time in the async delay
  //other wise have a short delay that repeats a spicific number of time untill it adds up to the difficulty time
  switch (ModeControl) {//cahnge modecontrol to something else
    case 0:
     ModeControl = 5;
     Serial.println("Looping To the End");
     break;
    case 1:
      Serial.print("Current effect: Randomcolor ");
      Serial.println(" case: 1");
      Randomcolor(); 
      break;
    case 2:
      Serial.print("Current effect: speckle ");
      Serial.println(" case: 2");
      speckle();
      break;
  }


  if(WrongAns){
    Serial.print("Wrong answer:(   ");
    Serial.print(" Score: ");
    Serial.println(Score);
    delay(6000);
    startvar = 0;//restart the begining sequence
    WrongAns = 0;
  }

  if(RightAns){
    Serial.print("Correct!  ");
    Score++;
    diffchange++;
    Serial.print(" Current score:");
    Serial.println(Score);
    RightAns = 0;
    CircuitPlayground.playTone(600,50);
    CircuitPlayground.playTone(450,50);
    CircuitPlayground.playTone(800,50);
  }

  if(diffchange <= 3){
    difficultylevel++;
    diffchange = 0;
  }



}//end main loop


//--------------------------------------the tasks' loops--------------------------------------
void pressrightbutton(){//put into a switch case so it keep replaying until the time is expired, then set WrongAns = 1;
  if(leftbuttonflag){
    WrongAns = 1;
  }else if(rightbuttonflag){
    RightAns = 1;
  } /*else if(){}//acceleromitor code
    WrongAns = 1;
  */
}

void pressleftbutton(){//put into a switch case so it keep replaying until the time is expired, then set WrongAns = 1;
  if(leftbuttonflag){
    RightAns = 1;
  }else if(rightbuttonflag){
    WrongAns = 1;
  } /*else if(){}//acceleromitor code
    WrongAns = 1;
  */
}

void acceleromitortask(){
   if(leftbuttonflag){
    WrongAns = 1;
  }else if(rightbuttonflag){
    WrongAns = 1;
  } /*else if(){}//acceleromitor code
    RightAns = 1;
  */
}

//----------------------------------------ISR LOOP----------------------------------------
void switchISR(){
  Switchflag = 1;
}

void rightbuttonISR(){
  rightbuttonflag = 1;
}

void leftbuttonISR(){
  leftbuttonflag = 1;
}

/*
//-----------------------------------MIDI function------------------------------------
//function for calcuating the freauency of the tone on MIDI scale
void generateMIDI(){
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
*/