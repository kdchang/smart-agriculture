#include <Wire.h>  // Arduino IDE 內建
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>
#include <dht.h>

int dht_dpin = 2; //定義訊號要從Pin 2 進來

dht DHT;

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

  stringOne = String("Temperature: ");
  stringTwo = String("Humidity   : ");  

  Serial.begin(9600);
  Serial.println("Humidity and temp\n\n");
  Serial.println("XD\n\n");  
}

void loop() {
  // Temp/Humanity
  DHT.read11(dht_dpin);   //去library裡面找DHT.read11
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C ");

  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.clear();
  stringThree = stringOne + DHT.temperature;
  lcd.print(stringThree);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  stringThree = stringTwo + DHT.humidity;
  lcd.print(stringThree);
  
  delay(1000);            //每1000ms更新一次

}
