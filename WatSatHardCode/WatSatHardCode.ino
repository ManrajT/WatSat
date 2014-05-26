#include <Wire.h>
#include <SBoard.h>
#include <HMC5883L.h>
/*
high pwm means low voltage
low pwm means high voltage
*/

const int NUM_BOARDS = 6;

// output pins for controlling the mux
int control0 = 2;
int control1 = 3;
int control2 = 4;
int control3 = 5;

// input pins for reading the mux
int in0 = 0;
int in1 = 1;

// output pins for controlling the magnetorquers
int torx = 6;
int tory = 7;
int torz = 8;
int torred = 9;

SBoard boards[NUM_BOARDS];
Data master [NUM_BOARDS];

char req;

void setup() {
  Serial.begin(9600);
  
  pinMode(control0, OUTPUT); 
  pinMode(control1, OUTPUT); 
  pinMode(control2, OUTPUT); 
  pinMode(control3, OUTPUT); 
  
  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  
  pinMode(torx, OUTPUT); 
  pinMode(tory, OUTPUT); 
  pinMode(torz, OUTPUT); 
  pinMode(torred, OUTPUT); 
  
  Serial.println("Started serial");
  init_stuff();
}

void loop() {
  while (Serial.available() > 0){
    listenForRequest();
  }
  
}

void listenForRequest(){
  req = Serial.read();
  
  if (req == 'g'){
    getRequest();
  }else if (req == 'p'){
    postRequest();
  }
}

void postRequest(){
  /*
  What to do when a "post" request is sent.
  For example, will post the voltage required to apply to magentorquers
  */
  delay(100);
  float a = Serial.parseFloat();
  Serial.println(a);
  adjust(a);
}

void getRequest(){
  /*
  What to do when a "get" request is sent.
  For example, will gather from all the sensors and pass that to comp using serial por
  */
 readall();
 outputall();
}

void init_stuff()
{
  // Defines all the sensors attached to the first mux
  Sensor p0 = {0, 0000, in0}, p01 = {0, 0111, in0}, p02 = {0, 1110, in0};
  Sensor p1 = {0, 0001, in0}, p11 = {0, 1000, in0}, p12 = {0, 1111, in0};
  Sensor tmp = {0, 0010, in0}, tmp1 = {0, 1001, in0};
  Sensor mxm = {0, 0011, in0}, mxm1 = {0, 1010, in0};
  Sensor mxd = {0, 0100, in0}, mxd1 = {0, 1011, in0};
  Sensor mym = {0, 0101, in0}, mym1 = {0, 1100, in0};
  Sensor myd = {0, 0110, in0}, myd1 = {0, 1101, in0};

  // Defines all the sensors attached to the second mux
  Sensor tmp2 = {0, 0000, in1}, tmp3 = {0, 0111, in1}, tmp4 = {0, 1110, in1};
  Sensor mxm2 = {0, 0001, in1}, p15 = {0, 1000, in1}, p05 = {0, 1111, in1};
  Sensor mxd2 = {0, 0010, in1}, tmp5 = {0, 1001, in1};
  Sensor mym2 = {0, 0011, in1};
  Sensor myd2 = {0, 0100, in1};
  Sensor p03 = {0, 0101, in1}, p04 = {0, 1100, in1};
  Sensor p13 = {0, 0110, in1}, p14 = {0, 1101, in1};
  
  boards[0] = SBoard(p0, p1, tmp, mxm, mxd, mym, myd, 
    control0, control1, control2, control3);
  boards[1] = SBoard(p01, p11, tmp1, mxm1, mxd1, mym1, myd1, 
    control0, control1, control2, control3);
  boards[2] = SBoard(p02, p12, tmp2, mxm2, mxd2, mym2, myd2, 
    control0, control1, control2, control3);
  boards[3] = SBoard(p03, p13, tmp3, 
    control0, control1, control2, control3);
  boards[4] = SBoard(p04, p14, tmp4, 
    control0, control1, control2, control3);
  boards[5] = SBoard(p05, p15, tmp5, 
    control0, control1, control2, control3);
    
}

void readall(){
  // SOLDERING NOTE: MAKE SURE TO LINE UP OUTPUTS!!
  // can fix this by giving a board another var that describes it's input pin
  master[0] = boards[0].readData();
  master[1] = boards[1].readData();
  master[2] = boards[2].readData();
  master[3] = boards[3].readMinData();
  master[4] = boards[4].readMinData();
  master[5] = boards[5].readMinData();
}

void outputall(){
  for (int i=0; i<NUM_BOARDS; i++){
    Serial.print(i);
    Serial.print("{photodiodes:");
    Serial.print(master[i].pda);
    Serial.print("; mag_x:");
    Serial.print(0);
    Serial.print("; mag_y:");
    Serial.print(0);
    Serial.print(";}"); 
  }
  Serial.print("\n");
}

void adjust(float mag){
 /* the value of mag will depend on the voltage required to be applied to the 
    magnetorquers.
      torquer | key
      --------+--------
        x     | mag 
        y     | mag + 100
        z     | mag + 200
       red    | mag + 300
  */
  if (mag >= 300){
    analogWrite(torred, (mag-300));
  }else if (mag >= 200){
    analogWrite(torz, (mag-200));
  }else if (mag >= 100){
    analogWrite(tory, (mag-100));
  }else{
    analogWrite(torx, mag);
  }
}
