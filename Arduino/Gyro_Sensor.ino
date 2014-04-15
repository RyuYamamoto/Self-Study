#include <SoftwareSerial.h>

void setup()
{
   Serial.begin(115200);
}

void loop()
{
  int i;
  int x,y;
  
  for(i=0;i<100;i++){
    x += analogRead(0); 
    y += analogRead(1); 
  }
  
  x/=100;
  y/=100;
  
  Serial.println("X:");
  Serial.println(x);
  Serial.println("Y:");
  Serial.println(y);
  delay(500);
}

