const short buttonUpPin = 2; 
const short pinGround1 = buttonUpPin + 1;
const short buttonDownPin = 4;
const short pinGround2 = buttonDownPin + 1;
const short stepPin = 6;
const short dirPin = 7;

int stepCounter = 0;
       
int buttonUpState;
int buttonDownState;             
short upLastState = 0;
short downLastState = 0;

unsigned long upDebounceTime = 0; 
unsigned long downDebounceTime = 0;

unsigned long debounceDelay = 50;    

#include <AccelStepper.h>

AccelStepper stepper(1, stepPin, dirPin);

void setup() {
  pinMode(buttonUpPin, INPUT);
  pinMode(buttonDownPin, INPUT);
  pinMode(pinGround1, OUTPUT);
  pinMode(pinGround1, OUTPUT);
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(1000);
}

void loop() {
  debounceUp();
  debounceDown();
  stepper.moveTo(stepCounter);
  stepper.runSpeedToPosition();
  
}

void debounceUp() {
  int readingUp = digitalRead(buttonUpPin);
  if (readingUp != upLastState) {
    upDebounceTime = millis();
  }
  if ((millis() - upDebounceTime) > debounceDelay) {
    if (readingUp != buttonUpState) {
      buttonUpState = readingUp;
      if (buttonUpState == HIGH) {
        stepCounter++;
      }
    }
  }
  upLastState = readingUp;
}

void debounceDown() {
  int readingDown = digitalRead(buttonDownPin);
  if (readingDown != downLastState) {
    downDebounceTime = millis();
  }
  if ((millis() - downDebounceTime) > debounceDelay) {
    if (readingDown != buttonDownState) {
      buttonDownState = readingDown;
      if (buttonDownState == HIGH) {
        stepCounter--;
      }
    }
  }
  downLastState = readingDown;
}
