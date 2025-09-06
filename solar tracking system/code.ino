#define BLYNK_TEMPLATE_ID "................"
#define BLYNK_TEMPLATE_NAME "........"
#define BLYNK_AUTH_TOKEN "..................."

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <LiquidCrystal.h>

// WiFi credentials
char ssid[] = ".....";
char pass[] = ".......";

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

// Mode select (V4) Auto / Manual
BLYNK_WRITE(V4)
{
  autoMode = param.asInt();
 
}

// ------------------- SENSOR + DISPLAY -------------------
void sendSensor()
{
  int valueL = analogRead(LDR_LEFT);
  int valueR = analogRead(LDR_RIGHT);

  int solar = analogRead(SOLAR_PIN);
  solar = map(solar, 0, 4095, 0, 7);  // ESP32 ADC range fix

  // Send to Blynk
  Blynk.virtualWrite(V1, solar);
  Blynk.virtualWrite(V2, solar * 0.1);

  // LCD Display update
  lcd.setCursor(0, 1);
  lcd.print("                "); // clear old data
  lcd.setCursor(0, 1);
  lcd.print("Volt=");
  lcd.print(solar);
  lcd.print(" Amp=");
  lcd.print(solar * 0.1);

}

// ------------------- SUN TRACKER -------------------
void sunTracker()
{
  if (autoMode == 1) {
    int valueL = analogRead(LDR_LEFT);
    int valueR = analogRead(LDR_RIGHT);

    int diff = valueL - valueR;

    // Dead zone to prevent shaking
    if (abs(diff) > 100) {
      if (diff > 0 && servoPos < 180) {
        servoPos++;
      } else if (diff < 0 && servoPos > 0) {
        servoPos--;
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
