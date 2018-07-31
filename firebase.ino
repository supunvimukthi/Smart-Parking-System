#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include "ESP8266WiFi.h"

#define FIREBASE_HOST "mcparkingsystem.firebaseio.com"
#define FIREBASE_AUTH "1yKZ5q7bLtSHJnfrAX2b72Uljf9g5vNu5UCXT4JJ" 

#define WIFI_SSID "Smart-Parking"
#define WIFI_PASSWORD "abcdefgh"

#define LED 1
//int inputPin = 7;               // choose the input pin (for PIR sensor)            // we start, assuming no motion detected

void setup() {
  //pinMode(inputPin, INPUT);
  digitalWrite(LED, 0);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  //Serial.println(digitalRead(inputPin));
  if ( Serial.available() ) {
    String a=Serial.readString();
    Serial.println(a);
    if(a=="A0"){Firebase.setInt("parkinglots/parkinglot1/occ", 0);}
    if(a=="A1"){Firebase.setInt("parkinglots/parkinglot1/occ", 1);}
    if(a=="B0"){Firebase.setInt("parkinglots/parkinglot2/occ", 0);}
    if(a=="B1"){Firebase.setInt("parkinglots/parkinglot2/occ", 1);}
    if(a=="C0"){Firebase.setInt("parkinglots/parkinglot3/occ", 0);}
    if(a=="C1"){Firebase.setInt("parkinglots/parkinglot3/occ", 1);}
    if(a=="D0"){Firebase.setInt("parkinglots/parkinglot4/occ", 0);}
    if(a=="D1"){Firebase.setInt("parkinglots/parkinglot4/occ", 1);}
  }
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
}
