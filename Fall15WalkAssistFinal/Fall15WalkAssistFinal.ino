/* Fall15WalkAssistFinal.ino
 *  By Greg Boiczyk
 *  Actuator code by Chunghwan Kim, 4/25/15
 *  Code to test Walk-Assist knee prototype.  A button preddl (+5V) will be fed to arduino to simulate a contraction of biceps femoris
 *  Encoders used to limit knee flex angle to within desired bounds
 */
#define encoderPinA 2 // channel A connected to digital pin 2
#define encoderPinB 3// channel B connected to digital pin 3
#define buttonPin 4 // button in digital pin 4
#define Power 6         // Digital out 3 controls (on/off) signal relay 
#define Direc 7         // Digital out 4 controls (contraction/extension) signal relay 
#define angleMax 30 // maximum angle
#define angleMin 1.0 // minimum angle
#define buzzer 14 // digital pin 14
//#define emgThresh 700 // EMG threshhold voltage
//#define emgIn A3 //EMG connected to pin A3
volatile unsigned long encoderPos = 0; 
int buttonState = 0;
double encoderAngle = 0.0;
//int emgRead;
bool startup = true;
void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(Power, OUTPUT);   // digital 6 as output
  pinMode(Direc, OUTPUT);   // digital 7 as output
  pinMode(buzzer, OUTPUT);
  Serial.println("Startup");
    ext();
    delay(13000);
    encoderPos = 0;
    startup = false;
    Serial.println("attaching interupts");
    //output an frequency
   for(int i=0;i<80;i++)
   {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
    }
    attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, CHANGE);//interupt will trigger function whenever there is a change between LOW and HIGH on digital pin 1
  
}

void loop() {
  Serial.println("Loop");
    buttonState = digitalRead(buttonPin);
    encoderAngle = encoderPos*360/2048; //2048 pulses / 360 degrees
    Serial.println(buttonState);
    Serial.println(encoderAngle);
//    emgRead = analogRead(emgIn);
    if(encoderPos > 2048){ //if encoder rotates below 0 point (- rotation) or 1 full rotation, re-zero encoder. NOTE: Should not make a full rotation w/ device
      encoderPos = 0;
    }
    else if(encoderAngle < angleMax && buttonState == LOW){ // if encoder angle is less than max flexion angle and button pressed
      cont();
      }
    else if(encoderAngle > angleMin && buttonState == HIGH){ // if encoder angle is greater than or equal to min flexion angle and button not pressed, extend
      ext();
    }
    else{
      hold();
    }
  
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

void cont()                    //contract actuator (fold leg forward)
{
  digitalWrite(Power, HIGH);
  digitalWrite(Direc, HIGH);
  delay(100);
}

  
void ext()                    //extend actuator (extend leg backward)                    
{
  digitalWrite(Power, HIGH);
  digitalWrite(Direc, LOW);
  delay(100);
}


void hold()                    //stop moving, hold position
{
  digitalWrite(Power, LOW);
  delay(100);
}

