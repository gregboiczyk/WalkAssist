/* Prototype2TestNoEncoder.ino
 *  By Greg Boiczyk 4/11/2016
 *  Actuator code by Chunghwan Kim, 4/25/15
 *  Code to test Walk-Assist knee prototype 2.  Flexion/extension controlled by EMG from bicep fem and rect fem respectively
 *  No encoder angle.
 */
#define emgPinRF A6 //Pin for rect fem EMG - analog pin 6
#define emgPinBF A7 //pin for bicep fem EMG - analog pin 7
#define Power 6         // Digital out 3 controls (on/off) signal relay 
#define Direc 7         // Digital out 4 controls (contraction/extension) signal relay 
// theshhold is 1/2 of max read from testing on ring finger flexors. May need to be adjusted.
// Analog read value = voltage * 1023/5
#define emgThreshRF 260 // EMG threshhold voltage for rectus femoris - adjust this as needed
#define emgThreshBF 260 // EMG threshhold for biceps femoris - adjust this as needed
int emgReadRF; //EMG read for rectus femoris 
int emgReadBF; //EMG read for biceps femoris 
String rfOut;
String bfOut;
bool startup = true;
void setup() {
  Serial.begin(9600);
  pinMode(Power, OUTPUT);   // digital pin 6 as output
  pinMode(Direc, OUTPUT);   // digital pin 7 as output
  Serial.println("Startup");
    ext();
    delay(10);
    startup = false;
}

void loop() {
  emgRead();
  Serial.println("Loop");
  Serial.println(emgReadRF);
  Serial.println(emgReadBF);
    if(emgReadBF > emgThreshBF && emgReadRF < emgThreshRF){ // if emg thesh for bicep fem reached and emg thresh for rect fem not reached, contract
      cont();
      Serial.println("contracting");
      }
    else if(emgReadRF > emgThreshRF && emgReadBF < emgThreshBF){ // if emg threshhold for rect fem reached and emg thresh for biceps fem not reached, extend
      ext();
      Serial.println("extending");
    }
    else{
      hold();
      Serial.println("holding");
    }
  delay(500);
  }

void emgRead() // read voltage from EMG pins
{
  emgReadRF = analogRead(emgPinRF);
  emgReadBF = analogRead(emgPinBF);
}

void cont()                    //contract actuator (fold leg forward)
{
  digitalWrite(Power, HIGH); //power and direc pins high
  digitalWrite(Direc, HIGH);
  delay(100);
}

  
void ext()                    //extend actuator (extend leg backward)                    
{
  digitalWrite(Power, HIGH); //power pin high direc pin low
  digitalWrite(Direc, LOW);
  delay(100);
}


void hold()                    //stop moving, hold position
{
  digitalWrite(Power, LOW); //power pin low
  delay(100);
}

