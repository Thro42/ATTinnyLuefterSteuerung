/*****************************************************************
 * 3D Drucker Gehäuselüfter Steuerung mit ATTiny85
 *****************************************************************/
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 // DS18B20 on Pin 2
#define pwmPin  4      // select the pin for the fan driver - phisical pin 4
#define minTemp 2500   // Start the Fan at 25°
#define maxTemp 3500   // Maximum Fan speed at 35°
#define minPWM 55      // Start PWM value because the FAN need minimum to start
#define ledPin  1      // onbord LED

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int prwmOut = 0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(ledPin, OUTPUT); 

  sensors.begin();
  if (sensors.getDS18Count() != 0)
    sensors.setResolution(12);

}

void loop() {
   
  if (sensors.getDS18Count() != 0) {
    sensors.requestTemperatures();
    int temp = int(sensors.getTempCByIndex(0) * 100);
    if (temp < minTemp) {
      prwmOut = 0;
      digitalWrite(ledPin,LOW);
    } else {
      prwmOut = map( max(min(temp, maxTemp), minTemp), minTemp, maxTemp, minPWM, 255 );
      digitalWrite(ledPin,HIGH);
    }
  }
  analogWrite(pwmPin, prwmOut );
  delay(1000);

}
