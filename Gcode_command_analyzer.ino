void GcodeToInstructions(){
  if (newData == true){                              //If there is new data turn it into instructions
    Neraser();                                       //Erase the NXX commands on the begginning of each line
    switch(Command[0]){                              //After the line information has been erased if there was any, read the first letter of the command and decide which case applies
       case 'G':                                
         GGcode();                                    //In the case of a G command go to GGcode function
       break;
       
       case 'M':
         MGcode();                                    //In the case of a M command go to MGcode function
       break;

       case ';':                                      //In the case of a ; ignore the rest
       break;
       
       default:
        {
          UnknownCommand();         //In the case of anything else, send: Unknown Command
        }
        break;       
    }
    
  //Debugging_Serial_print();                           //Print position and other things for development purposes
  Serial.println("ok");
  newData = false;                                    //Set the newData flag false 
  } 
}

void Neraser(){
    if (Command[0] == 'N'){                           //Erase linenumber gcode commands that start with NXX.. If the command starts with N : 
      for(int i = 0; i<64;i++){                       //We have detected a N command so we want to skip till the next space to move it off the command
        if (Command[i] == ' '){                       //Detect the next space
          for(int j = 0; j<64;j++){                   //Run throught the entire command 
            Command[j]= Command[i+1+j];               //And move the gcode to the left in the array replacing the Nxx command
          }
          break;                                      //Break the for loop when you find the space
        }
      }
    }
}

int CommandNumberExtractor(){                         //Function that extracts the number after a command and returns it as an int
  String temp;                                        //temp is a String that will contain the command number while writing it before returning it
  temp = String("");                                  //The temp string is initialized empty to prevent weird information getting into the commands or getting mixed
  for (int i = 1; i < 4; i++){                        //Scan for 3 digits (because gcode commands are at most 3 digits long)
    temp += Command[i];                               //Append the read digits to the temp string
    if ((Command[i] == ' ' ) || (Command[i] == ';' ) || (Command[i] == '\n' ) || (Command[i] == '\0' ) || (Command[i] == '*' ) ) {         //If there is a space, a ';' an endline or a null (indicating that the number is finished) break the for loop 
      break;
    }
  }
  return temp.toInt();                                //Return the command value as an int
}

String SubCommandExtractor(int i){              
  String temp;                                  //temp is a String that will contain the position temporally before writing it to PosXYZ
  temp = String("");                            //The temp string is initialized empty to prevent weird information getting into the commands or getting mixed
  for (int j = i + 2; j < 64; j++) {            //Scan trhough the entire command (until another space or endline is found) after the X to read the position to which we have to move 
    temp += Command[j];                         //Store the numeric values in the string to be read afterwards
    if ((Command[j] == ' ' ) || (Command[j] == ';' ) || (Command[j] == '\n' ) || (Command[j] == '\0' ) || (Command[j] == '*' ) ) {         //If there is a space, a ';' an endline or a null (indicating that this attribute is finished and we can go to the next) break the for loop and write the stored numeric values into the PosXYZ X component (which is the [0])
      break;                                    //Break the loop to stop looking for numbers
    }
  }
  return temp;
}

void UnknownCommand(){
  Serial.print("echo:Unknown command: ");
  Serial.print('"');
  Serial.print(Command);
  Serial.println('"');
}
