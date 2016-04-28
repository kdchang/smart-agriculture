#include <dht.h>   
  
int dht_dpin = A0; //定義訊號要從Pin A0 進來  
int SENSOR_PIN = A1;

dht DHT;   
  
void setup(){   
Serial.begin(9600);   
Serial.println("Humidity and temp\n\n");   
}
  
void loop(){   
// Temp/Humanity  
DHT.read11(dht_dpin);   //去library裡面找DHT.read11  
Serial.print("Humidity = ");   
Serial.print(DHT.humidity);   
Serial.print("% ");   
Serial.print("temperature = ");   
Serial.print(DHT.temperature);   
Serial.println("C ");   
delay(1000);            //每1000ms更新一次   

// Light
value = analogRead(SENSOR_PIN);
  delay(200);
  Serial.println(value);
  Serial.println(analogRead(0)); 
  delay(100); 
}  
