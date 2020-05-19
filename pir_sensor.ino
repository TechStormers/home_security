#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* wifi_name = "Internet Lord";
const char* wifi_password = "iamworthy";

#define sensor D0
#define led1 D1
#define led2 D2

void setup () {
  Serial.begin(115200);
  WiFi.begin(wifi_name, wifi_password);
  pinMode(sensor,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://iot99.000webhostapp.com/servo/pir_data");
    int httpCode = http.GET();
    
    if(httpCode > 0){
    // start of fetching get process
      String response = "";
      response = http.getString();
      Serial.println(response);

      if(response=="on"){
         long a = digitalRead(sensor);
         Serial.println(a);
      
        if(a == HIGH){
        HTTPClient https;
        https.begin("http://iot99.000webhostapp.com/sms.php");
        int httpsCode = https.GET();
    
        if(httpsCode > 0){
      // start of fetching get process
        String pir_response = "";
        pir_response = https.getString();
        Serial.println(pir_response);
    }
    else
      Serial.println(httpsCode);
      
    https.end();
    // end of fetching get process
     digitalWrite(led1,1);
     digitalWrite(led2,1);
   }
  }
  else{
        digitalWrite(led1,0);
        digitalWrite(led2,0);
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
