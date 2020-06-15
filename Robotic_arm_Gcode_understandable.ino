#include<Servo.h>
Servo ro;
Servo revro;
Servo phy;
Servo theta;

void setup() {
  ro.attach(5);    //Violet cable
  revro.attach(11);  //White cable
  phy.attach(6);    //Blue
  theta.attach(3);   //Whitecable from 3 group
  
  Serial.begin(250000);                                    // Begin Serial communication 
  StartCode();                                             // Send the startcode
}

void loop() {
GcodeCommandReceive();
GcodeToInstructions();
}
