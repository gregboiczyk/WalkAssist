import processing.serial.*;
Serial myPort;
String val; // data received from serial port
PrintWriter output;
void setup(){
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  output = createWriter ("Voltage.csv");
}
void draw(){
  if (myPort.available() > 0){
    String SenVal = myPort.readString();
    if (SenVal != null) {
      output.println(SenVal);
    }
  }
  println(val);
}

void keyPressed(){
  output.flush();
  output.close();
  exit();
}