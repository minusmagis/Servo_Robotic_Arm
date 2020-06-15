extern float PosXYZ[3];
extern char Command[];
extern float Extruder;
extern int Feedrate;
extern int toolPower;

void Debugging_Serial_print(){
  Serial.println("");
  Serial.println("--------------Debugging Section-------------------");
  Serial.print("Received Command: ");
  Serial.println(Command);
  Serial.print("Understood Command: ");
  Serial.print(Command[0]);
  Serial.println(CommandNumberExtractor());
  Serial.print("X Position = ");
  Serial.println(PosXYZ[0]);
  Serial.print("Y Position = ");
  Serial.println(PosXYZ[1]);
  Serial.print("Z Position = ");
  Serial.println(PosXYZ[2]);
  Serial.print("E Position = ");
  Serial.println(Extruder);
  Serial.print("Feedrate = ");
  Serial.println(Feedrate);
  Serial.print("Tool Power = ");
  Serial.println(toolPower);
  Serial.println("--------------------------------------------------");
  Serial.println("");
}

