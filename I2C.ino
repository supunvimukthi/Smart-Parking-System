#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

#define STEPS 2038

int PARKING_1 = 6;
int PARKING_2 = 7;
int PARKING_3 = A2;
int PARKING_4 = A3;
int TRIG_PIN = 4; //ultrasonic sensor for car arrival detection
int ECHO_PIN = 5;

int hasObstacle = HIGH;
SoftwareSerial ESPserial(2, 3); // RX | TX
Stepper stepper(STEPS, 8, 10, 9, 11); // stepper motor to control the gate
LiquidCrystal_I2C lcd(0x3F, 16, 2); //lcd display at the gate

void setup() {
  pinMode(PARKING_1, INPUT);
  pinMode(PARKING_2, INPUT);
  pinMode(PARKING_3, INPUT);
  pinMode(PARKING_4, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(); //initialize the lcd
  lcd.backlight(); //open the backlight
  lcd.print("HELLO");
  Serial.begin(115200);
  ESPserial.begin(115200);
  // put your setup code here, to run once:
}

void loop() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 29 / 2;
  int parking_1 = digitalRead(PARKING_1);
  int parking_2 = digitalRead(PARKING_2);
  int parking_3 = digitalRead(PARKING_3);
  int parking_4 = digitalRead(PARKING_4);
  if (duration == 0) {
    Serial.print("Warning: no pulse from sensor");
  }
  Serial.print("TIME :");
  Serial.println(millis()); 
  Serial.print("Distance : ");
  Serial.println(distance);
  if (distance < 20 and (not(parking_1) or not(parking_2) or not(parking_3) or not(parking_4)) ) {
    lcd.clear();
    lcd.print("Vehicle Detected");
    lcd.setCursor(0,1);
    lcd.print("at the Gate");
    delay(2000);
    openGate();
    lcd.clear();
    lcd.print("Gate Closing");
    lcd.setCursor(0,1);
    lcd.print("in 20 seconds...");
    delay(20000);
    closeGate();
    lcd.clear();
  }
  
  delay(1000);
  String b="A : ";
  String c=" B : ";
  String d=" C : ";
  String e=" D : ";
  String a=b+parking_1+c+parking_2;
  String f=d+parking_3+e+parking_4;
  Serial.println(a+f);
  lcd.clear();
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print(f);
  //if(ESPserial.available()){
     // Serial.println(ESPserial.readString());}
  if(parking_1==LOW){ESPserial.write("A0");}else{ESPserial.write("A1");}
  delay(1000);
  if(parking_2==LOW){ESPserial.write("B0");}else{ESPserial.write("B1");}
  delay(2000);
  if(parking_3==LOW){ESPserial.write("C0");}else{ESPserial.write("C1");}
  delay(1000);
  if(parking_4==LOW){ESPserial.write("D0");}else{ESPserial.write("D1");}
}

void openGate() {
  stepper.setSpeed(6); // 1 rpm
  stepper.step(550); // do 2038 steps -- corresponds to one revolution in one minute
}
void closeGate() {
  stepper.setSpeed(6); // 6 rpm
  stepper.step(-550); // do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
}
