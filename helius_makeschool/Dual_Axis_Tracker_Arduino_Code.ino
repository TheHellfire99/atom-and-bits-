#include <Servo.h> // include Servo library 

Servo horizontal; // horizontal servo
int servoh = 180;     // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

Servo vertical;   // vertical servo 
int servov = 180;     // stand vertical servo

// LDR pin connections
//  name  = analogpin;
int ldrlt = 0; //LDR top left
int ldrrt = 1; //LDR top rigt
int ldrld = 2; //LDR down left
int ldrrd = 3 ; //ldr down rigt

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  horizontal.attach(9); 
  vertical.attach (10);
  horizontal.write(180);
  vertical.write(45);
  delay(3000);
}


void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; 
  int avd = (ld + rd) / 2; 
  int avl = (lt + ld) / 2; 
  int avr = (rt + rd) / 2; 

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
    
  if (-1*tol > dvert || dvert > tol) 
  {
  if (avt > avd)
  {
    servov = --servov;
     if (servov > 180) 
     { 
      servov = 180;
     }
  }
  else if (avt < avd)
  {
    servov= ++servov;
    if (servov < 0)
  {
    servov = 0;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) 
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < 0)
    {
    servoh = 0;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > 180)
     {
     servoh = 180;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime); 
}
