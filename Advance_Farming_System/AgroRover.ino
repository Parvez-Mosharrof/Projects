#include <Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>





Servo myservo;
 LiquidCrystal_I2C lcd(0x27,16,2);



int soilPercent;
int soil;
int m1a=7;
int m1b=6;
int m2a=8;
int m2b=9;

int m1pwm=5;
int m2pwm=3;

int ira=4;
int irb=10;

int relay =13;

int agro=2;
int agro_value;
int gas=12;
int gas_value;
 
 int speedm1=100;
 int speedm2=85;



 
void setup() {
Serial.begin(9600);
lcd.begin();
 myservo.attach(11);
  
  pinMode(relay,OUTPUT);

    pinMode(m1a,OUTPUT);
    pinMode(m1b,OUTPUT);
    pinMode(m2a,OUTPUT);  // FOR MOTTOR 
    pinMode(m2b,OUTPUT);
    pinMode(m1pwm,OUTPUT);
    pinMode(m2pwm,OUTPUT);

      pinMode(ira,INPUT);
      pinMode(irb,INPUT);// for IR Sensor 
     
          
          pinMode(agro,INPUT);
          pinMode(gas,INPUT);
          digitalWrite(relay,HIGH);

    myservo.write(90);
    delay(500);


  lcd.clear();
  lcd.setCursor(0,0); lcd.print("AgroRover Active");
  lcd.setCursor(0,1); lcd.print("Waiting Msg...");

}





void loop()


{
        


 
    gas_value=digitalRead(gas);
    agro_value=digitalRead(agro);
 

     
      





 

    
           if(gas_value == 1)
              {
                               lcd.clear();
                               lcd.setCursor(0,0); lcd.print("Msg Received");
                               lcd.setCursor(0,1); lcd.print("GAS LEAK ALERT!");
                               delay(5000);

                               lcd.clear();
                               lcd.setCursor(0,0); lcd.print("Moving Leak Area");
                               lcd.setCursor(0,1); lcd.print("Please Wait...");
                               
                                    delay(1000);

                                    forword();
                                    delay(500);

                                      while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==0 && y==1)
                                         {
                                          stop();
                                           break;
                                         }
                                      }                   

                                      right();

                                     while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==1 && y==0)
                                         {
                                          stop();
                                           break;
                                         }
                                      }    

                                         forword();

                                      while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==0 && y==1)
                                         {
                                          stop();
                                           break;
                                         }
                                      }    
                                      
                                 lcd.clear();
                                 lcd.setCursor(0,0); lcd.print("Checking............");
                                 lcd.setCursor(0,1); lcd.print("Temp & Air");
                                 delay(8000);

                                  lcd.clear();
                                  lcd.setCursor(0,0);   lcd.print(" Monitoring....");
                                  lcd.setCursor(0,1);   lcd.print("   All Normal  ");
                                  delay(5000);

                                lcd.clear();
                                lcd.setCursor(0,0); lcd.print("Task Complete!");
                                lcd.setCursor(0,1);lcd.print("Returning Home");
                                delay(3000);
                              
                               
                                backword();

                                      while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==1 && y==0)
                                         {
                                          stop();
                                           break;
                                         }
                                      }      

                                      rightb();
                                      
                                      while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==0 && y==1)
                                         {
                                          stop();
                                           break;
                                         }
                                      }      
                                    backword();

                                      while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==1 && y==1)
                                         {
                                          stop();
                                           break;
                                         }
                                      }  

                         lcd.clear();
                         lcd.setCursor(0,0); lcd.print("AgroRover Active");
                         lcd.setCursor(0,1); lcd.print("Waiting Msg...");

                                    

                               
 
              }
    




                              if(agro_value == 1)
                            {
                               lcd.clear();
                               lcd.setCursor(0,0); lcd.print("Msg Received");
                               lcd.setCursor(0,1); lcd.print("Starting Task...");
                               delay(5000);

                               lcd.clear();
                               lcd.print("Moving to Field"); lcd.setCursor(0,1); lcd.print("Please Wait...");
                                delay(2000);

                                    forword();
                                    delay(500);

                                      while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==1 && y==0)
                                         {
                                          stop();
                                           break;
                                         }
                                      }
                                   
                                         
                              
                                    delay(500);
                                    right();
                                    delay(1200);
                                    stop();



                               for(int i=70;i>=0;i=i-5)
                               {
                                myservo.write(i);
                                delay(200);
                               }
                                 lcd.clear();
                                 lcd.print("Checking Soil..."); lcd.setCursor(0,1); lcd.print("Please Wait...");
                                 delay(1000);
                              
                                for(int g=0;g<=20;g++)
                                {
                                soil=analogRead(A1);
                                delay(1000);
                                }

                                soilPercent = map(soil, 1023, 0, 0, 100);
                                  lcd.clear();
                                  lcd.print("Checking Soil...");lcd.setCursor(0,1); lcd.print(soilPercent);lcd.print("%");
                                 delay(5000);


                                 if(soilPercent >= 50) 
                                  {
                                 lcd.clear();
                                 lcd.print("Soil Moist OK"); lcd.setCursor(0,1); lcd.print("No Water Needed.");
                                 delay(5000);
                                  }
                                  else
                                  { 
                                    lcd.clear();
                                    lcd.print("Soil Dry!"); lcd.setCursor(0,1); lcd.print("Water Needed.");
                                    delay(5000);
                                    lcd.clear();
                                    lcd.print("Watering Plants"); lcd.setCursor(0,1); lcd.print("Please Wait...");
                                    
                                   digitalWrite(relay,LOW);
                                    delay(7000);
                                   digitalWrite(relay,HIGH);
                                    delay(1000);
                                  }

                                    lcd.clear();
                                    lcd.print("Task Complete!"); lcd.setCursor(0,1); lcd.print("Returning Home.");
                                    delay(5000);

                          
                                

                                  
                             for(int i=0;i<=70;i=i+5)
                               {
                                myservo.write(i);
                                delay(200);
                               }

                                   delay(3000);
                                    rightb();
                                    delay(650);
                                    stop();
                                   backword();
                                   
                                       while(1)
                                      {
                                        int x=digitalRead(ira);
                                        int y=digitalRead(irb);
                                         
                                         if(x==1 && y==1)
                                         {
                                          stop();
                                           break;
                                         }
                                      }
                                   

                                      lcd.clear();
                                      lcd.setCursor(0,0); lcd.print("AgroRover Active");
                                      lcd.setCursor(0,1); lcd.print("Waiting Msg...");

                                


             
                            }


 delay(1000);




 }


void backword() 
{
   analogWrite(m1pwm,speedm1);
     analogWrite(m2pwm,speedm2);
  
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
}


void forword()
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
  digitalWrite(m1b,LOW);
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);

}

void right()
{
      analogWrite(m1pwm,speedm1);
      analogWrite(m2pwm,speedm2);
   digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  digitalWrite(m2a,LOW);
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
     digitalWrite(m1a,HIGH);
    digitalWrite(m1b,LOW);
    digitalWrite(m2a,LOW);
    digitalWrite(m2b,LOW);
  }

