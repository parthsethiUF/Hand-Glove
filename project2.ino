/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
#include "I2Cdev.h"
#include "MPU6050.h"
#include <LiquidCrystal.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int16_t ax, ay, az;
int16_t gx, gy, gz;
int po=0;
int d1=8,d2=7,d3=10,d4=9;
int b1=0,b2=0,b3=0,b4=0;
int high =  13;
#define OUTPUT_READABLE_ACCELGYRO
String out="";
String oo="";
int i = 0;
int f1,f2,f3,f4;
// the setup routine runs once when you press reset:
void setup() {
     #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    Serial.begin(9600);
    accelgyro.initialize();
    lcd.begin(16, 2);
    pinMode(high, OUTPUT);
    digitalWrite(high, HIGH);
      pinMode(d1, INPUT);
      pinMode(d2, INPUT);
      pinMode(d3, INPUT);
      pinMode(d4, OUTPUT);
    digitalWrite(d4, LOW);  
   

}

String check(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  i=0,f1=0,f2=0,f3=0,f4=0;
 if(az<0 && ax>14000&& ay<4000)
 {
 i=0;
 }
 else if(ay>4000&&ax<14000 && az <5000)
 {i=1;}
 else if(az>5000&&ax<5000)
 {i=2;}
       int a = analogRead(A0);int y = map(a, 0, 1023, 0, 102300);
        int a1 = analogRead(A1);int y1= map(a1, 0, 1023, 0, 102300);
         int a2 = analogRead(A2);int y2 = map(a2, 0, 1023, 0, 102300);
          int a3 = analogRead(A3);int y3 = map(a3, 0, 1023, 0, 102300);
           int a4 = analogRead(A6);int y4 = map(a4, 0, 1023, 0, 102300);
  // print out the value you read:
      // delay in between reads for stability
//----------------------------read sense--------------------------------------
    if(y>1100) // straight
    f1=1;
    else if(y<400)  //full bent
    f1=3;
    else   //half bent
    f1=2;

    if(y1>50)
    f2=1;
//    else if(y1<100)
//    f2=3;
    else
    f2=2;
    
    if(y2>1400)
    f3=1;
    else if(y2<400)
    f3=3;
    else 
    f3=2;

    if(y3>2500)
    f4=1;
    else 
    f4=2;
//----------------------------read sense--------------------------------------
if(b1+b2+b3>0)
{

if(b2==HIGH && b3==LOW)
  {out += "n";po++;}


if(b3==HIGH && b2==LOW)
 {out += "m";po++;}

if(y<800 && i==0 && b2==HIGH && b3==HIGH)
{out += "e";po++;}

if(y>800  && i==0 && b2==HIGH && b3==HIGH)
{out += "x";po++;}

if(y>1200 && f3!=1 && f4!=1 && y4>600 && y4<1500 && i==0 && b1== HIGH&& b2!=HIGH && b3!=HIGH)
{out += "r";po++;}

if( y<500 && f2==2 && f3!=1 && f4!=1 &&   y4<1000  && i==0 && b1== HIGH && b2==LOW &&b3==LOW)
{out += "o";po++;}

}
 else{ 
  if(f1==3 && f2!=1 && f3==3 && f4==2 && y4>1400 && i==0)
  {out += "a";po++;}
  if(f1==1 && f2==1 && f3==1 && f4==1 && y4<1000 && i==0)
  {out += "b";po++;}
  if(((f1==2 && f2!=1 && f3==2 && f4==2) || ((f1+f2+f3==7 || f1+f2+f3==6) && f4==2 && f1!=1 && f2!=1) ) &&   y4>1300  && i==0 && b1== LOW)
  {out += "c";po++;}
  if(f1==1&& f2!=1 && f3!=1 && f4==2 && y4<2000 && i==0)
  {out += "d";po++;}
  

  
  if(f1!=1 && f2==1 && f3!=3 && f4==1  && y4>2000 && i==0)
  {out += "f";po++;}
  if(f1==1&& f2!=1 && f3!=1 && f4==2 && i==1)
  {out += "g";po++;}
    if(f1!=3&& f2==1 && f3!=1 && i==1)
  {out += "h";po++;}
      if(f1!=1&& f2!=1 && f3!=1 && f4==1 &&  y4<1500 && i==0 )
  {out += "i";po++;}
      if(f1!=1&& f2!=1 && f3!=1 && f4==1 && y4<1500 && i==1)
  {out += "j";po++;}
  if(f1==1&& f2==1 && f3!=1 && f4==2 && y4>1500 && i==0)
  {out += "k";po++;}
  if(f1==1&& f2!=1 && f3!=1 && f4==2 && y4>1800 && i==0)
  {out += "l";po++;}

                                                                    
                                                                  

  if(f1==1&& f2==1 && f3!=1 && f4!=1  && i==2)
  {out += "p";po++;}
  
  if(f1==1&& f2!=1 && f3!=1 && f4!=1 && y4>1000 && y4<3000 && i==2)
  {out += "q";po++;}


  if(y<400 && f2!=1 && f3!=1 && f4!=1 &&   y4<1400  && i==0)
  {out += "s";po++;}

    if(y>400 && y<1000 && f2!=1 && f3!=1 && f4!=1 &&   y4<1400  && i==0)
  {out += "t";po++;}
                                                                    
                                                                    
  if(f1==1&& f2!=1 && f3!=1 && f4==1 && y4>400 && y4<1900 && i==0)
  {out += "u";po++;}

  if(f1==1&& f2==1 && f3!=1 && f4!=1 && y4>600 && y4<1500 && i==0)
  {out += "v";po++;}

  
  if(f1==1&& f2==1 && f3==1 && f4!=1 && y4>400 && y4<1500 && i==0)
  {out += "w";po++;}



  if(f1!=1 && f2!=1 && f3!=1 && f4==1 && y4>1500 && i==0)
  {out += "y";po++;}
  
  if(f1==1 && f2==1 && f3!=1 && f4==1 && y4>500 && i==0)
  {out += "z";po++;}


  if(f1==1 && f2==1 && f3==1 && f4==1 && i==0&& y4>1500)
  {out = "";po=0;}

  
  if(f1!=1 && f2!=1 && f3!=1 && f4!=1 && i==2)
  {out.remove(po-1);
  if(po>0||po==0)
  po--;}
 }
       Serial.print(i);Serial.println(po); Serial.println("\t");
                     Serial.println(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
                    Serial.print(f1);Serial.print("--");Serial.print(f2);Serial.print("--");Serial.print(f3);Serial.print("--");Serial.print(f4);Serial.print("--");Serial.println(y4);
                    Serial.print(y);Serial.print("--");Serial.print(y1);Serial.print("--");Serial.print(y2);Serial.print("--");Serial.print(y3);Serial.print("--");Serial.println(y4);
                     Serial.println(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
    /*   Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        
        Serial.println(gz);*/
        
        return out;
}
// the loop routine runs over and over again forever:
void loop() {
  b1 = digitalRead(d1);
    b2 = digitalRead(d2);
      b3 = digitalRead(d3);
 
  String o1=check();

  delay(200); 
  Serial.println("================");
  //Serial.print(b1);Serial.print(b2);Serial.println(b3); 
  //Serial.println("================");
  Serial.println(o1);lcd.print(o1);  
  Serial.println("================");
  if(b2==HIGH &&b3==HIGH)
  {
   delay(2000);
  }
  else{
  if(b1+b2+b3<2)
  delay(2000);
  else
  delay(1);
  }
}
