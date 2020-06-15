extern boolean AbsolutePos;
extern float currentPosXYZ[];                           //Declare external variables for use in this part of the script
extern float PosXYZ[];
extern int Feedrate;
extern boolean AllowedPosition;
const float pi = 3.14159265;


void MoveServos() {                                     //Function for moving the servos around sinchronously
  //  Serial.println("Move Servos Checked");            //For Development purposes
  float Resolution = 0;                                 //Resolution parameter, determines the fines step the servos will perform. It is dependant on the feedrate and if the command is G1 or G0
  float XYZtemp[] = {0, 0, 0};                          //This variable will store temporally the points inbetween the start and the finish point to trace as straight lines as possible
  float XYZmove[] = {0, 0, 0};                          //This variable stores the direction vector towards which we want the arm to move
  if (AbsolutePos == true)                                      //If the arm is in absolute position movement calculate the coordinates for the moving vector
  {
    //Serial.println("Absolute Check");
    for (int i = 0; i < 3; i++) {                   //Scan the PosXYZ and calculate the distance between the desired position and the current position in each axis
      XYZmove[i] = PosXYZ[i] - currentPosXYZ[i];    //Store the value of the direction vector
    }
    //        Serial.print("Movement in the x position: "); //For development purposes
    //        Serial.print(XYZmove[0]);
    //        Serial.print(" Movement in the y position: ");
    //        Serial.print(XYZmove[1]);
    //        Serial.print(" Movement in the z position: ");
    //        Serial.println(XYZmove[2]);                   //For development purposes
  }

  else {                                       //If the arm is in relative position movement use the coordinates as the moving vector
    {
      //Serial.println("Relative Check");
      for (int i = 0; i < 3; i++) {                   //Scan the PosXYZ and set it to be the direction vector since the arm is in relative position movement
        XYZmove[i] = PosXYZ[i];                       //Store the value of the direction vector
      }
      //        Serial.print("Movement in the x position: "); //For development purposes
      //        Serial.print(XYZmove[0]);
      //        Serial.print(" Movement in the y position: ");
      //        Serial.print(XYZmove[1]);
      //        Serial.print(" Movement in the z position: ");
      //        Serial.println(XYZmove[2]);                   //For development purposes
    }
  }

  Resolution = sqrt(sq(XYZmove[0]) + sq(XYZmove[1]) + sq(XYZmove[2])) * 1000 / Feedrate;

  for (int j = 0; j <= Resolution; j++) {         //Calculate as many intermediate points as the resolution variable
    for (int k = 0; k < 3 ; k++) {                //Store the value of each coordinate of the intermediate points within the variable XYZtemp[]
      XYZtemp[k] = currentPosXYZ[k] + (((j + (0.01 / ((j * 1000) + 1))) * XYZmove[k]) / (Resolution + 0.01));
    }
    if ((sqrt(sq(XYZtemp[0]) + sq(XYZtemp[1]))) < 60) {     //I the travel path of the robot arm falls whithin its body, rearrange the travel coordinates so as to describe a circle around it keeping a 60 mm distance at all times between the head and the body of the arm
      XYZtemp[1] = sqrt(3600 - sq(XYZtemp[0]));
    }
    XYZtoPolarMove(XYZtemp);
    Serial.print("X position = ");                //For development purposes
    Serial.print(XYZtemp[0]);                     //For development purposes
    Serial.print(" Y position = ");               //For development purposes
    Serial.print(XYZtemp[1]);                     //For development purposes
    Serial.print(" Z position = ");               //For development purposes
    Serial.println(XYZtemp[2]);                   //For development purposes
  }
  for (int l = 0; l < 3; l++) {                   //Store the position at which the arm has moved as the current position since it is, if the movement went as planed, the current position of the arm
    currentPosXYZ[l] = XYZtemp[l];
  }
  //  Serial.print("Current Position X = ");          //For development purposes
  //  Serial.print(currentPosXYZ[0]);                 //For development purposes
  //  Serial.print(" Y = ");                          //For development purposes
  //  Serial.print(currentPosXYZ[1]);                 //For development purposes
  //  Serial.print(" Z = ");                          //For development purposes
  //  Serial.println(currentPosXYZ[2]);               //For development purposes

}

float XYZtoPolarMove(float Pos2XYZ[]) {
  float posro = 0;
  float posrevro = 0;
  float posphy = 0;
  float r = 0;
  float postheta = 0;

  posro = atan((Pos2XYZ[0] + 0.001) / (Pos2XYZ[1] + 0.001)) * (180 / pi);
  r = sqrt(sq(Pos2XYZ[0]) + sq(Pos2XYZ[1]));
  r = constrain(r, 50, 900);
  posphy = (90 - ((atan((-Pos2XYZ[2] * sqrt(90000 - sq(r) - sq(Pos2XYZ[2])) + r * sqrt(sq(r) + sq(Pos2XYZ[2]))) / (r * sqrt(90000 - sq(r) - sq(Pos2XYZ[2])) + Pos2XYZ[2] * sqrt(sq(r) + sq(Pos2XYZ[2]))))) * 180 / pi));
  postheta = (-(atan((r * sqrt(90000 - sq(r) - sq(Pos2XYZ[2])) - Pos2XYZ[2] * sqrt(sq(r) + sq(Pos2XYZ[2]))) / (Pos2XYZ[2] * sqrt(90000 - sq(r) - sq(Pos2XYZ[2])) + r * sqrt(sq(r) + sq(Pos2XYZ[2])))) * 180 / pi));

  //  Serial.print("PremappingMapping coordinates:  posro: ");
  //  Serial.print(r);                             // Print on the serial port the coordinates written on the motors (For debugging purposes)
  //  Serial.print("  posphy: ");
  //  Serial.print(posphy);
  //  Serial.print("  postheta: ");
  //  Serial.println(postheta);

  posro = map(posro, -90, 90, 550, 2400);
  posrevro = map(posro, -90, 90, 2400, 550);
  posphy = map(posphy, 28, 132, 1100, 2350);
  postheta = map(postheta, -97, 34, 1250, 2750);

  //  Serial.println("PostMapping coordinates");
  //  Serial.println(posro);                             // Print on the serial port the coordinates written on the motors (For debugging purposes)
  //  Serial.println(posphy);
  //  Serial.println(postheta);

  posro = constrain(posro, 550, 2400);                 // Constrain the coordinates within the limits of the servo motor and the mechanics of the arm
  posrevro = constrain(posro, 550, 2400);
  posphy = constrain(posphy, 1100, 2350);
  postheta = constrain(postheta, 1250, 1000 + posphy);
  postheta = constrain(postheta, 1250, 2750);

  //  Serial.println("Final coordinates");
  //  Serial.println(posro);                             // Print on the serial port the coordinates written on the motors (For debugging purposes)
  //  Serial.println(posphy);
  //  Serial.println(postheta);
  //  Serial.println("MOVED");

  ro.writeMicroseconds(posro);
  revro.writeMicroseconds(posrevro);
  phy.writeMicroseconds(posphy);
  theta.writeMicroseconds(3300 - postheta);

}

boolean PositionAllowed() {                                 //Check if the position to which the command tells the arm to move is within the arm range, and if so return true, otherwise return false
  if (AbsolutePos == true) {
    float r = sqrt(sq(PosXYZ[0]) + sq(PosXYZ[1]));            //r cannot be bigger than 260, Y cannot be smaller than 60, Z has its own equation that determines which values are allowed and which aren't
    float ZmaxRange = -0.0072 * sq(r) + 1.6806 * r + 134.56;  //This is the equation that defines the maximum range for z for each value of r
    if ( (60 <= (int)r) && ((int)r <= 200) && (0 <= PosXYZ[2]) && ( PosXYZ[2] <= ZmaxRange)) {    //If the desired position is whithin this range the movement is allowed
      //      Serial.println("Whithin range Abs");                           //For development purposes
      return true;

    }
    else {
      //      Serial.println("Out of range Abs");                           //For development purposes
      return false;

    }
  }
  else {
    float XYZfinal[] = {0, 0, 0};                             //Create a variable that will hold the final position to prevent moving beyond the set boundaries of the arm in relative mode
    for (int v = 0; v < 3; v++) {                             //Set the final position to the sum of the current position plus the amount we want to move in each direction
      XYZfinal[v] = PosXYZ[v] + currentPosXYZ[v];
    }
    float r2 = sqrt(sq(XYZfinal[0]) + sq(XYZfinal[1]));         //r2 cannot be bigger than 260, Y cannot be smaller than 60, Z has its own equation that determines which values are allowed and which aren't
    float ZmaxRange2 = -0.0072 * sq(r2) + 1.6806 * r2 + 134.56;  //This is the equation that defines the maximum range for z for each value of r
    Serial.print("X final position = ");                              //For development purposes
    Serial.print(XYZfinal[0]);                                    //For development purposes
    Serial.print(" Y final position = ");                            //For development purposes
    Serial.print(XYZfinal[1]);                                       //For development purposes
    Serial.print(" Z final position = ");                           //For development purposes
    Serial.println(XYZfinal[2]);                                     //For development purposes
    Serial.print(" r2 final position = ");                           //For development purposes
    Serial.println(r2);                                    //For development purposes
    Serial.print(" ZMaxRange2 final position = ");                           //For development purposes
    Serial.println(ZmaxRange2);                                    //For development purposes
    if ( (60 <= (int)r2) && ((int)r2 <= 200) && (0 <= XYZfinal[2]) && ( XYZfinal[2] <= ZmaxRange2)) {  //If the final calculated position is whithin this range the movement is allowed
      //      Serial.println("Whithin range rel");                           //For development purposes
      return true;

    }
    else {
      //      Serial.println("Out of range rel");                           //For development purposes
      return false;

    }
  }
}
