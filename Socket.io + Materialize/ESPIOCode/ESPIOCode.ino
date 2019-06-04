/*******************Esp8266_Websocket.ino****************************************/

#include <ESP8266WiFi.h> 
//#include <WebSocketClient.h> //remember to add library
//#include <SocketIoClient.h>
#include "DHT.h"
#include <ArduinoJson.h>

#define DHTPIN D2     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

volatile unsigned long previousMillis2;
boolean handshakeFailed=0;
float data[2];

char path[] = "";   //identifier of this device

const char* ssid     = "enter your wifi ssid here";
const char* password = "enter your wifi password here";
char* host = "192.168.0.23";  //replace this ip address with the ip address (remember ipconfig)
const int espport= 3000;
  
//SocketIoClient webSocketClient;
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval=300; //interval for sending data to the websocket server in ms

// Use WiFiClient class to create TCP connections
//WiFiClient client;



void setup() {
  Serial.begin(9600); //depends on what you set it to  
/*
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

  delay(1000);//3000
  
  wsconnect();
  //  wifi_set_sleep_type(LIGHT_SLEEP_T);
  */
}

void loop() {
  delay(1000);
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
/*
  if (client.connected()) {
    currentMillis=millis(); 
    webSocketClient.getData(data); 
    
    if (data.length() > 0) {
      Serial.println(data);
      //*************send log data to server in certain interval************************************
      //currentMillis=millis();   
      if (abs(currentMillis - previousMillis) >= interval) {
        previousMillis = currentMillis;
           //***************************************SET DATA HERE******************************************
           data[0] = dht.readHumidity();
           data[1] = dht.readTemperature();
        JsonObject& info= jsonBuffer.createObject();
        info["humidity"] = data[0];
        info["temperature"] = data[1];
        
        webSocketClient.emit("updata", myJson);
        }
      }
      else{
    }*/
    delay(5);

  }

/*
void wsconnect(){
  // Connect to the websocket server
  if (client.connect(host, espport)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
      delay(1000);  
   
   if(handshakeFailed){
    handshakeFailed=0;
    ESP.restart();
    }
    handshakeFailed=1;
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    
    Serial.println("Handshake failed.");
   delay(4000);  
   
   if(handshakeFailed){
    handshakeFailed=0;
    ESP.restart();
    }
    handshakeFailed=1;
  }
}
*/
