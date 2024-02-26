#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
#define led D5

const char *ssid = "Lenovo";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led,OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // Your code here
  client=server.available();
  if(client==1){
    String request=client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request=="GET /ledOn HTTP/1.1"){
      digitalWrite(led,HIGH);
    }
    if (request=="GET /ledOff HTTP/1.1"){
      digitalWrite(led,LOW);
    }
  }
}
