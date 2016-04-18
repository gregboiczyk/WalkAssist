/* Fall15WalkAssistFinal.ino
 *  By Greg Boiczyk
 *  Actuator code by Chunghwan Kim, 4/25/15
 *  Code to test Walk-Assist knee prototype.  A button preddl (+5V) will be fed to arduino to simulate a contraction of biceps femoris
 *  Encoders used to limit knee flex angle to within desired bounds
 */
#define buttonPin 4 // button in digital pin 4
#define Power 6         // Digital out 3 controls (on/off) signal relay 
#define Direc 7         // Digital out 4 controls (contraction/extension) signal relay 
int buttonState = 0;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(Power, OUTPUT);   // line to state digital 3 as output
  pinMode(Direc, OUTPUT);   // line to state digital 4 as output
}

void loop() {
    buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);
    if(buttonState == LOW){ // button pressed
      Serial.println("contract");
      cont();
      }
    else if(buttonState == HIGH){ //button not pressed, extend
      Serial.println("extend");
      ext();
    }
    else{
      Serial.println("hold");
      hold();
    }
  
  }


void ext()                    //contract actuator (fold leg forward)
{
  Serial.println("e");
  digitalWrite(Power, HIGH);
  digitalWrite(Direc, HIGH);
  delay(50);
}

  
void cont()                    //extend actuator (extend leg backward)                    
{
  Serial.println("c");
  digitalWrite(Power, HIGH);
  digitalWrite(Direc, LOW);
  delay(50);
}


void hold()                    //stop moving, hold position
{
  Serial.println("h");
  digitalWrite(Power, LOW);
  delay(50);
}



