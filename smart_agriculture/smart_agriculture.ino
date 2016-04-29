#include <dht.h>
#include <Servo.h>
#include <Wire.h>  // Arduino IDE 內建
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>

int HUMID_TEMPERATURE = A0; //定義訊號要從Pin A0 進來
int WATER = A1;
int LIGHT = A2;
//int TRIGPIN = 2;//super sound wave
//int ECHOPIN = 4;//super sound wave
int MOTOR = 2;
int WATER_THRESHOLD = 670;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);// 設定 LCD I2C 位址


dht DHT;
Servo myservo;
int degree;

void setup() {
  Serial.begin(9600);
  Serial.println("Humidity and temp\n\n");
  Serial.println("XD\n\n");

  lcd.begin(16, 2);      // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
  for (int i = 0; i < 3; i++) {
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
  String Temperature = String("Temperature:");
  String Humidity = String("Humidity   :");
  lcd.setCursor(0, 0);
  lcd.print(Temperature);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print(Humidity);

  //pinMode(TRIGPIN, OUTPUT);
  //pinMode(ECHOPIN, INPUT);
  pinMode(HUMID_TEMPERATURE, INPUT);
  pinMode(LIGHT, INPUT);
  pinMode(WATER, INPUT);
  pinMode(MOTOR, OUTPUT);

  myservo.attach(MOTOR, 500, 2400); // 修正脈衝寬度範圍
  degree = 90;
  myservo.write(degree); // 一開始先置中90度
  delay(2000);
}

void loop() {
  DHT.read11(HUMID_TEMPERATURE);   //去library裡面找DHT.read11
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println(" C ");

  // Light
  int lightValue = analogRead(LIGHT);
  Serial.print("light = ");
  Serial.println(lightValue);

  int waterValue = analogRead(WATER);
  Serial.print("water sensor = ");
  Serial.println(waterValue);

  //super sound wave
  //digitalWrite(TRIGPIN, LOW);
  //delayMicroseconds(2);
  //digitalWrite(TRIGPIN, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(TRIGPIN, LOW);
  //double dist = pulseIn(ECHOPIN, HIGH); // 58.2; // 公分
  //Serial.print("dist = ");
  //Serial.println(dist);

  lcd.setCursor(12, 0); // 設定游標位置在第一行行首
  lcd.print(DHT.temperature);
  lcd.setCursor(12, 1); // 設定游標位置在第二行行首
  lcd.print(DHT.humidity);

  if (waterValue < WATER_THRESHOLD) {
    if(degree > 20) {
      motorDegreePlus(-1);
    }
  } else {
    if(degree < 90) {
      motorDegreePlus(1);
    }
  }

  delay(1000);
  Serial.println();

}

void motorDegreePlus(int delta) {
  degree += delta;
  setDegree(degree);
}

void setDegree(int degree0) {
  degree = degree0;
  myservo.write(degree0);
}

