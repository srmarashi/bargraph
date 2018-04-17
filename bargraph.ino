//Bargraph meter by: seyed roohollah marashi
// srmarashi@yahoo.com
// 00436763832008

//settings for leds and smoothing
const int NUMLED = 10; //number of outputs
const int NUMSAMPLE = 20; //Samples taken. More = Smoother but also slower.

const int DELAY = 1; //Delay to keep it stable

//which pins are you using for inputs?
const int refPIN = A0; //this value should always be zero
const int voltPIN = A2; //this is the audio input pin

//which pins are you using for outputs?
const int ledPIN[NUMLED] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //Number of each output pin

//value scaling. change these to make it more or less sensitive.
//the analog input signal ranges from 0 to 1024, so find some numbers in between there.
const int voltTHRESH[NUMLED] = {5, 10, 20, 25, 30, 40, 50, 60, 70, 80}; //Value asscociated on an ON led


#include <Wire.h>




#define BACKLIGHT_PIN     13



int vREF = 0; //Sets reference voltage to 0 (leave this alone)

//sample variables for smoothing (leave these alone)
int SAMP[NUMSAMPLE] = {0}; //value of sample
int INDEX = 0; //number of sample from 1-[NUMSAMPLE]
int TOTAL = 0; //running total of sample values
int AVG = 0; //average of sample values over [NUMSAMPLE]
int sum = 0;
int sum1 = 0;

void setup() {
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );

  //Setup for the smoother
  for (int READ = 0; READ < NUMSAMPLE; READ++) { //initalizes readings
    SAMP[READ] = 0; //sets readings to 0
  }
  //setup for the led outputs
  for (int p = 2; p <= (NUMLED + 1); p++) { //cycles through pins 2-6
    pinMode(p, OUTPUT); //sets the current pin to OUTPUT
  }
  //setup for analogue inputs
  pinMode(refPIN, INPUT);
  pinMode(voltPIN, INPUT);

}

void loop() {

  TOTAL -= SAMP[INDEX];
  SAMP[INDEX] = analogRead(voltPIN);
  TOTAL += SAMP[INDEX++];

  if (INDEX >= NUMSAMPLE) {
    INDEX = 0; //resets INDEX to 0, restarting the process
  }
  AVG = TOTAL / NUMSAMPLE; //Calculates the average

  //Here is where the led control starts
  int vREF = analogRead(refPIN); //sets vREF to the value of our reference pin


  for (int i = 0; i < NUMLED; i++) { //runs through each led until all have been checked
    if (AVG >= vREF + voltTHRESH[i]) //finds out if the led should be on
      {
        digitalWrite(ledPIN[i], HIGH); //sets the current PIN to HIGH if true

      }
      
      else
      {
        digitalWrite(ledPIN[i], LOW); //sets the current PIN to LOW if false

      }
  
    delay(DELAY);
  }
}

