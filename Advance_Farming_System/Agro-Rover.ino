#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int servo=11;
int m1a=3;
int m1b=2;
int m2a=4;
int m2b=5;
int m1pwm=9;
int m2pwm=10;
int ira=6;
int irb=7;
int irc=8;
int relay =A0;

int agro=12;
int agro_value;
int gas=13;
int gas_value;
 
 int speedm1=100;
 int speedm2=100;

void setup() {
Serial.begin(9600);
lcd.begin();

  pinMode(servo,OUTPUT);
  pinMode(relay,OUTPUT);

    pinMode(m1a,OUTPUT);
    pinMode(m1b,OUTPUT);
    pinMode(m2a,OUTPUT);  // FOR MOTTOR 
    pinMode(m2b,OUTPUT);
    pinMode(m1pwm,OUTPUT);
    pinMode(m2pwm,OUTPUT);

      pinMode(ira,INPUT);
      pinMode(irb,INPUT);// for IR Sensor 
      pinMode(irc,INPUT);
          
          pinMode(agro,INPUT);
          pinMode(gas,INPUT);



}

void loop()

 {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AgroRover Active");
     lcd.setCursor(0, 1);
     lcd.print("Monitoring......");


  gas_value=digitalRead(gas);
  agro_value=digitalRead(agro);
int gas_value=1;
int agro_value=0;


  if(gas_value == 1)
  {
       lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS LEAK ALERT!");
  lcd.setCursor(0,1);
  lcd.print("Locating Area..");
  delay(2000);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Moving to Leak");
  lcd.setCursor(0,1);
  lcd.print("Location...");
  delay(2000);


     forword() ;
      delay(500);
  
           while(1)
           {
               int x= digitalRead(ira);
               int y= digitalRead(irb);

                 if(x== 1 && y== 0)
                   {
                      stop();
                  
                       break;
                   }
            }
   
  
    right();
           while(1)
           {
               int x= digitalRead(ira);
               int y= digitalRead(irb);

                 if(x== 0 && y== 1)
                   {
                      stop();
                
                       break;
                   }
            }
   
     forword();

           while(1)
           {
               int x= digitalRead(ira);
               int y= digitalRead(irb);

                 if(x== 1 && y== 0)
                   {
                      stop();
                
                       break;
                   }
           }


lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Checking Temp");
   delay(15000);
  lcd.setCursor(0,1);
  lcd.print("All Normal");
  delay(5000);


   backword();

      while(1)
           {
               int x= digitalRead(ira);
               int y= digitalRead(irb);

                 if(x== 0 && y== 1)
                   {
                      stop();
                
                       break;
                   }
            }
   rightb() ;
     while(1)
           {
               int x= digitalRead(ira);
               int y= digitalRead(irb);

                 if(x== 1 && y== 0)
                   {
                      stop();
                  
                       break;
                   }
            }
   backword();
while(1)
           {
               int x= digitalRead(ira);
               int y= digitalRead(irb);

                 if(x== 1 && y== 1)
                   {
                      stop();
                  
                       break;
                   }
            }

  }



     else if(agro_value == 1)
     {


    }

delay(500);
 }

void forword() 
{
     analogWrite(m1pwm,speedm1);
     analogWrite(m2pwm,speedm2);
  
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);

}


void backword()
{
     analogWrite(m1pwm,speedm1);
     analogWrite(m2pwm,speedm2);
   
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);

}

void left()
{
       analogWrite(m1pwm,speedm1);
       analogWrite(m2pwm,speedm2);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);

}

void right()
{
      analogWrite(m1pwm,speedm1);
      analogWrite(m2pwm,speedm2);
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);

}

void stop()
  {
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);

  }
  void rightb()
{
      analogWrite(m1pwm,speedm1);
      analogWrite(m2pwm,speedm2);
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  }

