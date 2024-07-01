#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float v2 = 0;
int readval;
int ppm = 0;
float totalv = 0;
float finalv = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  //red
  pinMode(7, OUTPUT);
  //blue
  pinMode(8, OUTPUT);
  //green
  pinMode(A3, INPUT);
  Serial.begin(9600);
  lcd.begin();
  for (int c = 0; c < 70; c++){
    readval = analogRead(A3);
    v2 = (readval/1023.0) * 3.3;
    totalv = totalv + v2;
    delay(500);
  }
  finalv = totalv / 70.0;
  ppm = (8020 * finalv * finalv) - (3170 * finalv) + 830;
  if (ppm > 5000) {
    ppm = 4999;
  }
  
  if (ppm >= 3501 && ppm <= 5000){
    digitalWrite(2, HIGH);
    //red
  }
  if (ppm > 500 && ppm <= 900){
    digitalWrite(7, HIGH);
    //blue
  }
  if (ppm > 1001 && ppm <= 3000){
    digitalWrite(8, HIGH);
    //green
  }
  lcd.print(finalv);
  lcd.setCursor(0,1);
  lcd.print(ppm);
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay to print in a less speedy way
//reading from A3 and getting middle voltage
}
