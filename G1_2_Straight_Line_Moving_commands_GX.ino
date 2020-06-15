float PosXYZ[] = {0, 170.0, 15.0};
float Extruder = 0;
int Feedrate = 500;
int toolPower = 0;
float currentPosXYZ[] = {0, 170.0, 15.0};                   //The values at which the servos naturally start
extern boolean AbsolutePos;


void MovingCommand() {
  bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
  if (AbsolutePos == false) {
    for (int v = 0; v < 3; v++) {                           //Reinitialize the value of desired position before reading the new desired value
      PosXYZ[v] = 0;
    }
  }
  else{
    for (int v = 0; v < 3; v++) {                           //Reinitialize the value of desired position before reading the new desired value
      PosXYZ[v] = currentPosXYZ[v];
    }
  }
  for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
    if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
      switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction
        case 'X':                                         //If the case is X it means we want to change the X position so we will scan the following numbers to know to which position we have to move
          {
            PosXYZ[0] = SubCommandExtractor(i).toFloat();
            //        Serial.println("X checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'Y':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            PosXYZ[1] = SubCommandExtractor(i).toFloat();
            //        Serial.println("Y checked");                //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'Z':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            PosXYZ[2] = SubCommandExtractor(i).toFloat();
            //        Serial.println("Z checked");                //For development purposes
          }
          break;                                           //Break the loop to continue looking for other attributes

        case 'E':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            Extruder = SubCommandExtractor(i).toFloat();
            //        Serial.println("E checked");                //For development purposes
          }
          break;

        case 'F':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            Feedrate = SubCommandExtractor(i).toFloat();
            //        Serial.println("F checked");                //For development purposes
          }
          break;

        case 'S':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            toolPower = SubCommandExtractor(i).toFloat();
            //        Serial.println("F checked");                //For development purposes
          }
          break;

        case ';':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        case '\n':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        case '\0':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        case ' ':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        default:
          {
            UnknownCommand();                                 //In the case of anything else, send: Unknown Command
            endMarker = true;                                 //And break the for loop that was looking for other attributes of the G command
          }
          break;
      }
    }
    else if (endMarker == true) {
      break;
    }
  }
    if (PositionAllowed() == true){
      MoveServos();
    }
    else{
      Serial.println("Coordinate out of range!");
    }
}
