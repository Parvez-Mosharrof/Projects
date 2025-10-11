#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>


LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial mySerial(13,12);
int sensor ;
int relay=16;
int ir=14;

void setup() {
  lcd.begin();
  Serial.begin(9600);
  mySerial.begin(115200);
  pinMode(relay,OUTPUT);
   digitalWrite(relay,HIGH);
}

void loop() {
  sensor= analogRead(A0);
    lcd.setCursor(0, 0);
    lcd.print("sensor value:");
    lcd.print(sensor);



  if( sensor > 250)
  {
        lcd.setCursor(0, 0);
      lcd.print("  gas leakage   ");
      lcd.setCursor(0, 1);
       lcd.print("  Polluted Air  ");
      delay(5000);


     lcd.setCursor(0, 0);
     lcd.print("   Calling......");
     lcd.setCursor(0, 1);
     lcd.print("   Landowner    ");
      delay(5000);


     lcd.setCursor(0, 0);
     lcd.print("  Gas leakage...");
     lcd.setCursor(0, 1);
     lcd.print("  Message Rover ");
     digitalWrite(relay,LOW);
     delay(5000);
    digitalWrite(relay,HIGH);
    


     lcd.setCursor(0, 0);
     lcd.print("  Message.......");
     lcd.setCursor(0, 1);
     lcd.print("  Fire Station  ");
     SendMessage();

      delay(5000);

     lcd.setCursor(0, 0);
     lcd.print("  Calling.......");
     lcd.setCursor(0, 1);
     lcd.print("  Fire Station  ");
      MakeCall();


    delay(60000);


  }
  else
   {
      lcd.setCursor(0, 1);
     lcd.print("   Clean Air    ");
   }

delay(1000);
}



void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801744340859\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Gas leak! Location: https://maps.app.goo.gl/scue7Jk1Bckxnpak7");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(6000);
}


void MakeCall()
{
  mySerial.println("ATD+8801744340859;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(6000);
}





