//LDC
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const int columns=16;
const int rows=2;
int mapRange = 40;
int wait=0;
//motor
int motorPin=6;
int speed;
//encoder
int pinA=3;
int pinB=2;
int lastPinA;
int valueA;
int speedDisplay;
boolean clockwise;
long int encoderCount=0;

void setup() {
  //LCD
  lcd.begin(columns,rows);
  //motor
  pinMode(motorPin,OUTPUT);
  //encoder
  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);
  lastPinA=digitalRead(pinA);
  Serial.begin(9600); 
}

void loop() {
  valueA=digitalRead(pinA);
  delay(wait);
  if(valueA!=lastPinA){
    if(digitalRead(pinB)!=valueA){
      encoderCount++;
      lcd.clear();
    }
    else{
      encoderCount--;
      lcd.clear();
    }
    if(encoderCount>=mapRange){
      encoderCount=mapRange;
    }
    speed=map(encoderCount,0,mapRange,175,255);
    speed = constrain(speed, 0, 255);
    if(encoderCount<=0){
      encoderCount=0;
      speed=0;
      lcd.clear();
    }
    lcd.setCursor(0,0);
    lcd.print("Fan Speed");
    lcd.setCursor(0,1);
    lcd.print(encoderCount);
    Serial.println(speed);
    Serial.println(encoderCount);
    delay(wait);
    analogWrite(motorPin,speed);
  }
  lastPinA=valueA;
}


