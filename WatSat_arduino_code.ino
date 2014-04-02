//All code is using variables, which can change

int inputNum = 0;  //value from 0 to 15, telling which line on the MUX to select and in this form to easily convert to binary that's need for control lines 



void setup() {
  Serial.begin(9600);

  pinMode(control1, OUTPUT); 
  pinMode(control2, OUTPUT); 
  pinMode(control3, OUTPUT); 
  pinMode(control4, OUTPUT); 

}

void loop() {
  Serial.println((value>>n) & 1
}



void selectInputs(int inputNum){
  //given number of the input lines we'd like, activate the control lines which select them
  //same input lines will be selected from both MUXes
  
  if(inputNum < 16 && inputNum > 0){
    
  }
//convert inputLine 
  
  if(controlLines
  digitalWrite(control1);
  digitalWrite(control2); 
}











float readPhotoDiode(int pin){
/*
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
*/
  sensorValue = analogRead(pin);
  float voltage = sensorValue * (5.0 / 1023.0); 
  return voltage; 
}


