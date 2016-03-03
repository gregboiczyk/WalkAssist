// Created 12/15/2015 by Greg Boiczyk
// Based on code from http://playground.arduino.cc/Main/RotaryEncoders

#define encoderPinA 2 // channel A connected to digital pin 2
#define encoderPinB 3// channel B connected to digital pin 3
#define buttonPin 4 // button in digital pin 4
volatile unsigned long encoderPos = 0; 
int buttonState = 0;
double encoderAngle = 0.0;
void setup() {
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);


  attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, CHANGE);//interupt will trigger function whenever there is a change between LOW and HIGH on digital pin 1
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  encoderAngle = encoderPos*360/2048; //2048 pulses / 360 degrees
  Serial.println(encoderAngle);
  //Serial.println(encoderPos);
  if(buttonState == LOW){
    encoderPos = 0; // zero encoder if button is pressed
  }
  delay(1000);
}

void doEncoderA(){
  if(digitalRead(encoderPinA) == HIGH){
    //check channel B to see which way encoder turning
    if (digitalRead(encoderPinB) == LOW){
      encoderPos--; // encoder turning clockwise, increment down
    }
    else{
      encoderPos++; // encoder turning ccw, increment up
    }
    }
    else{
      if(digitalRead(encoderPinB) == HIGH){
        encoderPos--;   //cw
      }
      else{
        encoderPos++; //ccw
      }
    }
}
    
  


void doEncoderB(){
  if(digitalRead(encoderPinB) == HIGH){
    if(digitalRead(encoderPinA) == HIGH){
      encoderPos--; //CW
    }
    else{
      encoderPos++;
    }
  }
  else{
    if(digitalRead(encoderPinA) == LOW){
      encoderPos--;
    }
    else{
      encoderPos++;
    }
  }
}

