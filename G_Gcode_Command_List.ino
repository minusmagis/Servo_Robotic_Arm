boolean AbsolutePos = true;
extern float PosXYZ[];

void GGcode(){                                  //Function that runs in the event of a GXX command (G1 or G0)
//  Serial.println("G Checked");                  //For development purposes
  switch(CommandNumberExtractor()){             //Read the command number after the G of the G command to know exactly which command it is
    case 0:                                     //Both the case 0 and the case 1 are treated equally
      MovingCommand();                          //Jump to the Moving Command Function
    break;

    case 1:                                     //Both the case 0 and the case 1 are treated equally
      MovingCommand();                          //Jump to the Moving Command Function
    break;

    case 4:                                     //If we have command G4 Go to Wait() function
      Wait();
    break;

    case 28:                                    //Case 28 is homing so move to the homing position (now it is set for the servo arm in which the homing position is {0,170.0,15.0} XYZ
      AbsolutePos = true;                       //Set the absolute positioning to true to be able to go to the home position accurately (NOTE THAT IF ON RELATIVE MODE HOMING WILL OVERRIDE TO ABSOLUTE MODE)
      PosXYZ[0] = 0;                            //Set the position to the homing position and move the servos
      PosXYZ[1] = 170.0;
      PosXYZ[2] = 15.0;
      MoveServos();
    break;

    case 90:
      AbsolutePos = true;                       //Set the Absolute position flag to true
    break;

    case 91:
      AbsolutePos = false;                      //Set the Absolute position flag to false to move in relative positions
    break;

    default:
    {
      UnknownCommand();                         //In the case of anything else, send: Unknown Command
    }
    break;
  }
}
