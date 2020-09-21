//Serial Part
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5, 6);

//Ultrasonic Part
const int trigPin = 9;
const int echoPin = 10;
long UltrasonicRawInput;
int UltrasonicDistance;

//Water Sensor Part
int WaterSensorValue = 0;  // holds the value
int WaterSensorAnalogPin = A0; // sensor pin used

//LDR part
int light;

void setup() {
  // put your setup code here, to run once:
  //Serial Part
  Serial.begin(115200);
  s.begin(9600);

  //Ultrasonic Part
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //LDR part
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Ultrasonic"] = getUltrasonicData();
  root["WaterSensor"] = getWaterSensorData();
  root["Light"] = getLDRData();
  root["Light LED"] = getLDRLed();
  root.printTo(s);
  delay(500);
  /*  if (s.available() > 0)
    {
      root.printTo(s);
    }*/
}

int getUltrasonicData() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  delay(250);
  digitalWrite(trigPin, LOW);
  UltrasonicRawInput = pulseIn(echoPin, HIGH);
  UltrasonicDistance = UltrasonicRawInput * 0.034 / 2;
  Serial.print("UltrasonicDistance:  ");
  Serial.println(UltrasonicDistance);
  return UltrasonicDistance;
}

int getWaterSensorData() {
  WaterSensorValue = analogRead(WaterSensorAnalogPin);
  Serial.print("Water : ");
  Serial.println(WaterSensorValue);
  return WaterSensorValue;
}

int getLDRData() {
  light = analogRead(A1);
  Serial.print("LDR : ");
  Serial.println(digitalRead(13));
  if (light < 100) {
    digitalWrite(13, HIGH);
  } else if (light > 100) {
    digitalWrite(13, LOW);
  }
  return light;
}

boolean getLDRLed() {
  return digitalRead(13);
}
