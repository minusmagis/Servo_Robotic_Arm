extern float currentPosXYZ[];

void GetCurrentPosition(){                    //Print the current coordinates stored in currentPosXYZ[] variable in the following form: X:0.00 Y:0.00 Z:0.00
  Serial.print("X:");
  Serial.print(currentPosXYZ[0]);
  Serial.print(" Y:");
  Serial.print(currentPosXYZ[1]);
  Serial.print(" Z:");
  Serial.println(currentPosXYZ[2]);
}
