
void parsing() {
  /*

    4  режим  $4 1 60; 0-звичайний, 1-holdreps, 2-bpm.
    6   каунтер $6 1 -200; 0-hold time, 1-reps.
    8   min maxDistance calibration $8; $8 200 300;
  */
  if (recievedFlag) {  // якщо отримали дані
    recievedFlag = false;
    switch (intData[0]) {
      case 4:
        mode = intData[1];
        if (intData[1] == 1) {
           minhold = intData[2];
           counter[0]=intData[2];
        } else if (intData[1] == 2)
          {TimerInterval = 60000UL / intData[2];}
        else if (intData[1] == 0)
          {TimerInterval = 1000;}
        break;
      case 6:
        counter[intData[1]] = intData[2];
        break;
      case 8:
        if(intData[1]==0){
        minDistance=distance[3];
        maxDistance=distance[3]+40;}
        else {
          minDistance=intData[1];
          if(intData[2]==0)
          {maxDistance=minDistance+40;}
            else{maxDistance=intData[2];}
        }
        Serial.print("minDistance: ");
        Serial.println(minDistance);
        Serial.print("maxDistance: ");
        Serial.println(maxDistance);
        break;
    }
  }
// Serial.print("scrollOffset"); Serial.println(scrollOffset);
  // ****************** парсінг *****************
  if (Serial.available() > 0) {
    char incomingByte;

    incomingByte = Serial.read();

    if (parseStarted) {
      if (incomingByte != divider && incomingByte != ending) {  // якщо не пробіл і не кінець
        string_convert += incomingByte;               
          // додаємо в рядок
      } else {
          intData[parse_index] = string_convert.toInt();
        string_convert = "";
        parse_index++;
      }
    }
    if (incomingByte == header) {
      parseStarted = true;
      parse_index = 0;
      string_convert = "";
      for (int i = 0; i < PARSE_AMOUNT; i++) intData[i] = 0;
    }
    if (incomingByte == ending) {
      parseStarted = false;
      recievedFlag = true;
    }
  }

}
