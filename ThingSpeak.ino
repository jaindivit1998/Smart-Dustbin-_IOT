#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <dht.h>
#include <ThingSpeak.h>

#define sensor D4   //Pin where output of dht11 goes

dht DHT;

WiFiClient client;

int dt, temp, humidity; 
int trigPin = 5;  //D1
int echoPin = 4;  //D2
unsigned long myChannelNumber=734665; 
const char * myWriteAPIKey = "B4AX32OKV698MONL";             // Channel Write API Key 

// WiFi parameters to be configured
const char* ssid = "Vivo";     //Access Point or Personal Hotspot
const char* password = "12345678";  //Access Point or Personal Hotspot password

void setup(void)
{ 
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  pinMode(sensor, INPUT);
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(500);
  
  // Connect to WiFi
  Serial.print("Connecting to "+*ssid);
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  
}
void loop() {
   long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;  // The speed of sound is 340 m/s or 29.1 microseconds per centimeter.
 // The ping travels out and back, so to find the distance of the
 // object we take half of the distance travelled.
 
  
  static boolean data_state= false;
//  dt=DHT.read11(sensor);
  temp=DHT.temperature;
  humidity=DHT.humidity;
  Serial.println(temp);
  Serial.println(humidity);
 Serial.print(distance);
  Serial.println("CM");
  delay(10);
  
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2,distance);
  
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
   delay(200);
  
}
