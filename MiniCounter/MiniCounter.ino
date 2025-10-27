#include <FastLED.h>
#include <Button.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <VL53L0X.h>



//Піни
#define LED_PIN 6

#define SbuttonPin 2
Button Mbutton(3);
Button Dbutton(4);
//Button Sbutton(2);


//DECLARATIONS///////////////////////////////////////////////

                                                //parsing
#define PARSE_AMOUNT 4
#define header '$'   //початок
#define divider ' '  //розділення
#define ending ';'   //кінець передачі
boolean parseStarted;
boolean recievedFlag;
boolean effectsFlag;
int intData[PARSE_AMOUNT];

byte parse_index;
String string_convert = "";
int effect = 0;

int16_t mode=0;
int16_t minhold=0;
unsigned long beatInterval;
boolean completion[3];

                                                        //sensor

VL53L0X sensor;
bool sensorOK = true;

//5-18
//8-24
int minDistance=270;
int maxDistance=310;
int distance[4];
int pdistance = 0;


int counter[]={0,0};
String counterStr="0";
boolean SimpCounter[]={1,1};
boolean isin = 0;
boolean in = 0;
boolean ignoreFirstSecond = 1;
int16_t timerDisplay;


unsigned long lastTimerUpdate = 0;
unsigned long TimerInterval = 1000;

int min_distance[5];  // масив для збереження останніх х значень відстані



// Прототипи функцій
void Buttons();
void DistanseChecking();
void Timer();


void setup() {
  Serial.begin(9600);

//кнопки
  Dbutton.begin();
  Mbutton.begin();
  pinMode(SbuttonPin, INPUT_PULLUP);

//сенсор

  Wire.begin();
  if (!sensor.init()) {
  Serial.println("Failed to detect and initialize sensor!");}
  sensor.setTimeout(200);
  sensor.setSignalRateLimit(0.75);
  sensor.setMeasurementTimingBudget(20000);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 12);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 8);
  sensor.startContinuous(20);


}


void loop() {
  //Serial.print("distance"); Serial.println(distance);

  parsing();
  Buttons();
  DistanseChecking();
  Timer();
}

