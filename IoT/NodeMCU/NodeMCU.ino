#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

SoftwareSerial s(D6, D5);
const char* ssid = "Jio 4G 404";
const char* password =  "9137312358";


void setup() {
  //LED
  pinMode(13, OUTPUT);
  pinMode(16, OUTPUT);
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("..");
  }
  Serial.println("Connected to the WiFi network");
  while (!Serial) continue;

}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (WiFi.status() == WL_CONNECTED) {
    if (root == JsonObject::invalid()) {
      Serial.println("X");
      root.printTo(Serial);
      return;
    }
    else { //Upload Data
      HTTPClient http;
      Serial.println("JSON received and parsed");
      root.prettyPrintTo(Serial);
      http.begin("http://kaushikiot.herokuapp.com/putObj");
      http.addHeader("Content-Type", "application/json");
      char JSONmessageBuffer[300];
      root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      int httpResponseCode = http.PUT(JSONmessageBuffer);

      if (httpResponseCode > 0) {

        String response = http.getString();

        Serial.println(httpResponseCode);
        Serial.println(response);

      } else {

        Serial.print("Error on sending PUT Request: ");
        Serial.println(httpResponseCode);

      }
      http.end();
    }
    //Upload data finished
    readData13();
    readData9();

  }
  else {
    Serial.println("Error in WiFi connection");
  }
  Serial.println("---------------------xxxxx--------------------");
}

void readData13() {
  HTTPClient http;
  http.begin("http://kaushikiot.herokuapp.com/LED13");  //Specify request destination
  int httpCode = http.GET();                                                                  //Send the request
  if (httpCode > 0) { //Check the returning code
    String payload = http.getString();   //Get the request response payload
    Serial.println("Payload : " + payload);
    if (payload.equals("ON")) {
      digitalWrite(13, HIGH);
    }
    else if (payload == "OFF") {
      digitalWrite(13, LOW);
    }
  }
  http.end();
}

void readData9() {
  HTTPClient http;
  http.begin("http://kaushikiot.herokuapp.com/LED9");  //Specify request destination
  int httpCode = http.GET();                                                                  //Send the request
  if (httpCode > 0) { //Check the returning code
    String payload = http.getString();   //Get the request response payload
    Serial.println("Payload : " + payload);
    if (payload.equals("ON")) {
      digitalWrite(16, HIGH);
    }
    else if (payload == "OFF") {
      digitalWrite(16, LOW);
    }
  }
  http.end();
}
