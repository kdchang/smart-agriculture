#include <Wire.h>  // Arduino IDE 內建
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>

int temperature = 25;
int humidity = 50;
int light = 70;
String stringOne, stringTwo, stringThree;

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // 設定 LCD I2C 位址

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光

  // 閃爍三次
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); // 開啟背光
    delay(250);
    lcd.noBacklight(); // 關閉背光
    delay(250);
  }
  lcd.backlight();

  // 輸出初始化文字
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("DRC Hackathon");
  delay(1000);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print("Smart Plant Care");
  delay(3000);

  // 告知使用者可以開始手動輸入訊息
  //lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print("Use Serial Mon");
  //lcd.setCursor(0, 1);
  //lcd.print("Type to display");

  stringOne = String("Temperature: ");
  stringTwo = String("Humidity   : ");  
}

void loop() {
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.clear();
  stringThree = stringOne + temperature;
  lcd.print(stringThree);
  //delay(1000);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  stringThree = stringTwo + humidity;
  lcd.print(stringThree);

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  
  temperature = temperature+1;
  if (temperature>35) { temperature = 10;}
  humidity = humidity+5;
  if (humidity>100) { humidity =10;} 
}
