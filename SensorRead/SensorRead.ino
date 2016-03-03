//Based off code from http://tommydykes.com/archives/705
int sensor0;
 
void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
} 
void loop () {
 
sensor0 = analogRead(A6); // EMG connected to pin A6 
Serial.print(sensor0);
Serial.print(" , ");
Serial.println();
 
}
