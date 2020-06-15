void MGcode(){                                  //Function that runs in the event of a MXXX command More functionalities will be added with time as they are needed
  //Serial.println("M Checked");                //For development purposes
  switch(CommandNumberExtractor()){             //Read the command number after the M of the M command to know exactly which command it is
    case 21:
      Serial.println("echo:SD init fail");      //In case M21 (initialize SD) send an echo fail message stating that there was no SD
    break;

    case 114:
      GetCurrentPosition();                     //In case M114 Send the current position of the arm 
    break;
    
    case 115:
      FirmwareCapabilities();                   //In case M115 Send the firmware capabilities of this arm 
    break;

    default:
    {
      UnknownCommand();    //In the case of anything else, send: Unknown Command
    }
    break;
  }
}
