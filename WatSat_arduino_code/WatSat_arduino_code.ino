/*
high pwm means low voltage
low pwm means high voltage
*/

//All code is using variables, which can change
//Figure out how data for magnetometers have to be handled (photodiodes and temp are just default


int select = 1;  //value from 0 to 15, telling which line on the MUX to select and in this form to easily convert to binary that's need for control lines 

int control0 = 2;
int control1 = 3;
int control2 = 4;
int control3 = 5;

void setup() {
  Serial.begin(9600);
  
  pinMode(control0, OUTPUT); 
  pinMode(control1, OUTPUT); 
  pinMode(control2, OUTPUT); 
  pinMode(control3, OUTPUT); 
  
}

void loop() {
/*
  for(int i=1; i<16; i++){
    Serial.println(i);
    selectLine(i); 
    Serial.print(digitalRead(control3)); 
    Serial.print(digitalRead(control2)); 
    Serial.print(digitalRead(control1)); 
    Serial.print(digitalRead(control0)); 
    Serial.println(); 
    delay(1000);  
  }
*/
  if (Serial.available() <= 0){
    Serial.print('serial unavailable');
  }
  
  char in;
  while (Serial.available() > 0){
    in = Serial.read();
    Serial.print(in);
    delay(100);
  }
  
  /*
  Serial.println((value>>n) & 1
  
  // checks for if anything needs to be done 
  if (Serial.available() > 0){
    request_status = Serial.read();
    if (request_status == 1111){
      // TODO: get sensor data
    }else if (request_status == 0000){
      // TODO: activate actuators
    }
  }
  */
}



void selectLine(int inputNum){
  //given number of the input lines we'd like, activate the control lines which select them
  if(0 < inputNum && inputNum < 16){
    
    if (inputNum >= 8){
      digitalWrite(control3,HIGH);
      inputNum = inputNum - 8; 
    }
    else{
      digitalWrite(control3,LOW);
    }
     
    
    if (inputNum >= 4){
        digitalWrite(control2,HIGH);
        inputNum = inputNum - 4;
    }
    else{
        digitalWrite(control2,LOW);
    }
    
    
    
    if (inputNum >= 2){
       digitalWrite(control1,HIGH);
       inputNum = inputNum - 2;
    }
    else{
      digitalWrite(control1,LOW);
    }
    
    
    
    
    if (inputNum >= 1){
        digitalWrite(control0,HIGH);
        inputNum = inputNum - 1;
    }
    else{
        digitalWrite(control0,LOW);
    }
    
  
  }
}






/*

float readPhotoDiode(int pin){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);



  sensorValue = analogRead(pin);
  float voltage = sensorValue * (5.0 / 1023.0); 
  return voltage; 
}
*/
