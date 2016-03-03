/*
 Created 12/15/2015 by Greg Boiczyk
 Actuator code created 17 Jan 2009
 modified 25 March 2015
 by Kevin Lawrence
 modified 25 April 2015
 by Chunghwan Kim
 */

 //--------------------Variables setting-------------------------------------------------------
 
const int sw = 12;
const int Power = 6;         // Digital out 3 controls (on/off) signal relay 
const int Direc = 7;         // Digital out 4 controls (contraction/extension) signal relay 

//--------------------Set Up-------------------------------------------

void setup(){

  pinMode(Power, OUTPUT);   // line to state digital 3 as output
  pinMode(Direc, OUTPUT);   // line to state digital 4 as output
  Serial.begin(9600);      // initialize serial communications
}

//-------------Main Loop----------------------------------------------------

void loop() 
{
  Serial.println("extending");
   ext();
   delay(3000);
   Serial.println("holding");
   hold();
   delay(3000);
   Serial.println("contracting");
   cont();
   delay(3000);
   Serial.println("holding");
   hold();
   delay(5000);
}
//------------------------Subfunction---------------------------------------------------

void cont()                    //contract actuator (fold leg forward)
{
  digitalWrite(Power, HIGH);
  digitalWrite(Direc, HIGH);
  delay(50);
}

  
void ext()                    //extend actuator (extend leg backward)                    
{
  digitalWrite(Power, HIGH);
  digitalWrite(Direc, LOW);
  delay(50);
}


void hold()                    //stop moving, hold position
{
  digitalWrite(Power, LOW);
  delay(50);
}


