void Wait() {
  bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
  for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
    if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
      switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction
        case 'S':                                         //If the case is X it means we want to change the X position so we will scan the following numbers to know to which position we have to move
          {
          delay(SubCommandExtractor(i).toInt()*1000);
//        Serial.println("S checked");                    //For development purposes           
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'P':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
          delay(SubCommandExtractor(i).toInt());
//        Serial.println("P checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case ';':                                         //If the case is ; 
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
    else if (endMarker == true){
      break;
    }
  }
}
