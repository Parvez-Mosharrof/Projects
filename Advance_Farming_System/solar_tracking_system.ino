#define BLYNK_TEMPLATE_ID "TMPL6ywAefThD"
#define BLYNK_TEMPLATE_NAME "ppp"
#define BLYNK_AUTH_TOKEN "-m0ZDhwAkbnNG4uogr75Sb_wQmPyksn_"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <LiquidCrystal.h>

// WiFi credentials
char ssid[] = "parvez";
char pass[] = "parvezzahid";

BlynkTimer timer;
Servo myServo;

// LDR pins (ESP32 ADC pins)
#define LDR_LEFT 34
#define LDR_RIGHT 35
#define SOLAR_PIN 32
#define RELAY1 27  

// LCD pins
const int rs = 21, en = 22, d4 = 18, d5 = 19, d6 = 23, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Relay pin


// Variables
int servoPos = 90;   // initial servo pos (middle)
int autoMode = 1;    // 1 = Auto, 0 = Manual

// ------------------- BLYNK FUNCTIONS -------------------

// Relay control (V0)
BLYNK_WRITE(V0)
{
  int value1 = param.asInt();
  digitalWrite(RELAY1, value1);
}


// Servo manual control (V3)
BLYNK_WRITE(V3)
{
  if (autoMode == 0) { // Manual mode only
    servoPos = param.asInt();
    myServo.write(servoPos);
  }
}

// Mode select (V4) Auto / Manual
BLYNK_WRITE(V4)
{
  autoMode = param.asInt();
 
}

// ------------------- SENSOR + DISPLAY -------------------
void sendSensor()
{
  int  man= analogRead(SOLAR_PIN);
  double volt = (man * 3.5) / 4095.0;
   volt =volt*3.8 ;
   double amp; 
  double a;
   if(volt <2)
    {
      a=0.05;
    }
else if(volt <3)
    {
      a=0.06;
    }
else if(volt <4)
    {
      a=0.07;
    }
else if(volt <5)
     {
      a=0.08;
     } 
 else if(volt <6)
     {
       a=0.9;
     }
   else
     {
       a=0.1;
     }

 amp=volt*a;

  // Send to Blynk
  Blynk.virtualWrite(V1, volt);
  Blynk.virtualWrite(V2, amp);

  // LCD Display update
  lcd.setCursor(0, 1);
  lcd.print("                "); // clear old data
  lcd.setCursor(0, 1);
  lcd.print("Volt:");
  lcd.print(volt);
  
  lcd.print(" Amp:");
  lcd.print(amp);


}

// ------------------- SUN TRACKER -------------------
void sunTracker() {
  if (autoMode == 1) {
    int valueL = analogRead(LDR_LEFT);
    int valueR = analogRead(LDR_RIGHT);

    int offset =-50; // চাইলে +50 বা -50 দিয়ে টেস্ট করো
    int diff = (valueR - valueL) + offset;

    if (abs(diff) > 200) {   // Dead zone বড় করা হলো
      int step = 1;
      if (diff > 0 && servoPos < 170) {
        servoPos += step; 
      } else if (diff < 0 && servoPos > 10) {
        servoPos -= step; 
      }
      myServo.write(servoPos);
    }

    
  }
}

// ------------------- SETUP -------------------
void setup()
{

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("SOLAR OUTPUT");

  pinMode(RELAY1, OUTPUT);
  myServo.attach(14);  // Servo control pin (GPIO14 = PWM)

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timers
  timer.setInterval(1000L, sendSensor);  // প্রতি ১ সেকেন্ডে সেন্সর ডাটা
  timer.setInterval(300L, sunTracker);   // প্রতি ৩০০ms এ ট্র্যাকিং
}

// ------------------- LOOP -------------------
void loop()
{
  Blynk.run();
  timer.run();
}

