
bool lastButtonState = HIGH; 

void Buttons() {

/**
    if (profileMIndex == 0) {
      bool currentButtonState = digitalRead(SbuttonPin);
    if (currentButtonState == LOW && lastButtonState == HIGH) {
      counter--;
   //   Serial.println(counter);
      tone(7, 250, 100);
      MyText[1]=String(counter);
      drawText(MyText[1].c_str(), rows[1], CRGB::Red, 1);
      //Serial.print("Min5sec: "); Serial.println(min_distance[0]);
      Serial.println("1");
    }
    lastButtonState = currentButtonState;
  }*/  //Кнопка Д
  /**if (profileMIndex == 0) {
      bool currentButtonState = digitalRead(SbuttonPin);
    if (currentButtonState == LOW && lastButtonState == HIGH) {
      minDistance=distance[3];
      maxDistance=distance[3]+40;
      Serial.print("minDistance: ");
      Serial.println(minDistance);
    } else if (currentButtonState == HIGH && lastButtonState == LOW){
       //maxDistance=distance[3];
      Serial.print("maxDistance: ");
      Serial.println(maxDistance);
    }
    lastButtonState = currentButtonState;

  }**/

}

