#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#define servo D4

Servo myServo;
 
const char* wifi_name = "Internet Lord";
const char* wifi_password = "iamworthy";
 
void setup () {
  Serial.begin(115200);
  WiFi.begin(wifi_name, wifi_password);
  pinMode(servo,OUTPUT);
  myServo.attach(servo);
  myServo.write(160);
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://iot99.000webhostapp.com/servo/servo_data");
    int httpCode = http.GET();
    
    if(httpCode > 0){
    // start of fetching get process
      String response = "";
      response = http.getString();
      Serial.println(response);

      if(response=="lock"){
        myServo.write(160);
      }
      else{
        myServo.write(75);
      }
    }
    else
      Serial.println(httpCode);
      
    http.end();
    // end of fetching get process
  }
  else{
    delay(1000);
    Serial.print("Connecting..");
  }
}
