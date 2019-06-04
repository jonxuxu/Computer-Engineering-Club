/*******************Esp8266_Websocket.ino****************************************/

#include <ESP8266WiFi.h> 
#include <SocketIOClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN D2     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// Networking
const char* ssid     = "newhome";
const char* password = "maolan123";
char  host[] = "192.168.0.13";  //replace this ip address with the ip address (remember ipconfig)
int port = 3000;

// Socket and timer
SocketIOClient socket;
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval = 1000; //interval for sending data to the websocket server in ms

// JSON object setup
StaticJsonBuffer<200> jsonBuffer;
JsonObject& data = jsonBuffer.createObject();
String JSON;

void setup() {
  // Initilaizing objects
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Socket connect
  if (!socket.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  if (socket.connected()){
    Serial.println("connected to server");
  }

  // Set up json boi
  data["temp"] = 0;
  data["humidity"] = 0;
}

void loop() {
  currentMillis = millis(); 
  if (currentMillis - previousMillis > interval){
    previousMillis = currentMillis;
      float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
  
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Temperature: ");
    Serial.println(t);

    // Run when connected to wifi and host
    if (socket.connected()){ 
      JSON = "";
      data["temp"] = t;
      data["humidity"] = h;
      data.printTo(JSON);
      socket.emit("updateData", JSON);
    }
  }
}
