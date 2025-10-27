

void initSensor() {



  if (!sensorOK) {

    Wire.begin();
    if (sensor.init()) {
      sensorOK = true;
      sensor.setTimeout(200);
      sensor.setSignalRateLimit(0.75);
      sensor.setMeasurementTimingBudget(20000);
      sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 12);
      sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 8);
      sensor.startContinuous(20);
      Serial.println("Sensor Reinitialised!");
      delay(100);
    } else {
      Serial.println("Cant reconnect sensor!");
    }
  }
  if (sensor.timeoutOccurred() || (distance[0] <= 0 && distance[1] <= 0 && distance[2] <= 0 && sensorOK == true)) {
    sensorOK = false;
    Serial.println("Failed to detect and initialize sensor!");
  }
}


void DistanseChecking() {

  distance[2] = distance[1];
  distance[1] = distance[0];
  distance[0] = sensor.readRangeContinuousMillimeters();

  // Фільтрація (використовуємо тільки, якщо всі три виміри валідні)

  if (distance[0] < 8000 && distance[1] < 8000 && distance[2] < 8000) {
    if (abs(distance[3] - distance[0]) > 5) {
      distance[3] = distance[1];
    }
  } else {
    distance[3] = maxDistance + 40;
  }

  //Serial.println(distance[0]);
  //Serial.print("filtered:");
  //Serial.println(distance[3]);


  // Обробка події "вхід в зону"
  if (!isin && distance[3] <= minDistance && distance[3] > 30) {
    isin = true;
    if (mode != 2) {
      tone(7, 250, 100);
      Serial.println("1");

      //якщо не виключено то збільшуєм лічильник
    }
    if (mode == 0) {
      counter[1]++;
    }


   // Serial.print("counter[1]");
   // Serial.println(counter[1]);
  }


  // Обробка події "вихід із зони"
  else if (isin && distance[3] >= maxDistance && distance[3] < maxDistance + 1000) {
    isin = false;
    ignoreFirstSecond=1;
    completion[0] = 1;
    if (counter[1] == 0) {
      tone(7, 500, 300);
      counter[1]++;
      Serial.println("3");
    } else if (mode != 2) {
      tone(7, 100, 100);
    } 

    if (mode == 1) {
      counter[0] = minhold;
    } else if (counter[0] > 0)  //якщо не відлік то скидаєм до 0
    {
      counter[0] = 0;
    }
    Serial.println("2");
  }
}

void Timer() {
  if (millis() - lastTimerUpdate >= TimerInterval) {
    lastTimerUpdate = millis();
    initSensor();

    if (isin) { 
      if (ignoreFirstSecond==0){
      counter[0]++;}
      else {
        ignoreFirstSecond=0;
      } 
      }
    if (counter[0] == -1) {
      if (mode == 1) {
        counter[1]++;
        tone(7, 300, 100);
        Serial.println("4");
      } else {
        tone(7, 500, 300);
        Serial.println("3");
      }
      counter[0]++;
    }
                        //bpm mode
    if (mode == 2&&counter[1]<0) {

      if (completion[0] && completion[1]&& completion[2]) {
        counter[1]++;
        tone(7, 600, 20);
        Serial.println("4");
      } else if (completion[0])
        {tone(7, 600, 20);} 
        else
        {tone(7, 800, 5);}
      completion[2] = completion[1];
      completion[1] = completion[0];
      completion[0] = 0;
    }
  }
  //Serial.println(counter[0]);
}
