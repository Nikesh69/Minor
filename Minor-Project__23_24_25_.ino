/*     Arduino Based Color Sorter
 *      By BEI Students
 *      Roll No: 23, 24 & 25
 */

#include <Wire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
const int analogInPin = A3;
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color=0;
int buttonState = 0; 
int OrangeCount = 0;
int PurpleCount = 0;
int YellowCount = 0;
int GreenCount = 0;
int R = frequency;
int G = frequency;
int B = frequency;
void setup() {
lcd.begin(16,2);
lcd.backlight();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(A1, HIGH);
  
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("   WELCOME TO");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" Arduino Based");
lcd.setCursor(0,1);
lcd.print("  Color Sorter");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("This Project is");
delay(1000);
lcd.setCursor(0,1);
lcd.print("    Made By");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("     Prabas");
delay(1000);
lcd.setCursor(0,1);
lcd.print("     Pokhrel");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("     Norgen");
delay(1000);
lcd.setCursor(0,1);
lcd.print("     Moktan");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);  
lcd.print("    & Nikesh");
delay(1000);
lcd.setCursor(0,1);
lcd.print("      Baral");
delay(2000);
lcd.clear();

lcd.setCursor(0,0);
lcd.print("    Let's Go");
delay(1000);
lcd.setCursor(0,1);
lcd.print("System is Ready");
delay(1000);
}
void loop() {
int Ldr = analogRead(analogInPin);
buttonState = digitalRead(A0);
int Resetbutton = digitalRead(A2);
if(buttonState==HIGH & Ldr<400){
  
  topServo.write(110);
  delay(500);
Ldr = analogRead(analogInPin);
delay(10);
  if(Ldr<400){
  for(int i = 85; i > 48; i--) {
    topServo.write(i);
    delay(10);
  }
  delay(500);
  
  color = readColor();
  delay(10);  
  switch (color) {
    case 1:
    bottomServo.write(20);
    break;
    case 2:
    bottomServo.write(45);
    break;
    case 3:
    bottomServo.write(65);
    break;
    case 4:
    bottomServo.write(100);
   
  }
  delay(300);
  
  for(int i = 48; i > 12; i--) {
    topServo.write(i);
    delay(2);
    
  } 
  lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Ora:");
    lcd.print(OrangeCount);
    lcd.setCursor(0,1); 
    lcd.print("Pur:");
    lcd.print(PurpleCount);
    lcd.setCursor(9,0); 
    lcd.print("Yel:");
    lcd.print(YellowCount);
    lcd.setCursor(9,1); 
    lcd.print("Gre:");
    lcd.print(GreenCount);
  delay(200);
  
  for(int i = 12; i < 85; i++) {
    topServo.write(i);
    delay(2);
  }
  }
  color=0;

}
if(buttonState==LOW )
{
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" We're Stopping");
    delay(20);
    lcd.setCursor(0,1);
    lcd.print("   For Now :)");
    delay(1000);
    lcd.clear();
}
if(Resetbutton==HIGH)
{
OrangeCount = 0;
PurpleCount = 0;
YellowCount = 0;
GreenCount = 0;
   for(int i =0 ;i<5 ; i++)
{
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("System Resetting");
delay(1000);
lcd.setCursor(0,1);
lcd.print("   Please Wait");
delay(1000);
lcd.clear();

}
lcd.setCursor(0,0);
lcd.print("     Ready");
delay(1000);
    
}
if (buttonState==HIGH & Ldr>400)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("No Object Detect");
delay(20);
lcd.clear();
}

}
int readColor() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println("  ");
  delay(50);
  
  
  if(R<270 & R>210 & G<330 & G>280 & B<260 & B>200){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("     Orange");
    color = 1;
    OrangeCount = OrangeCount+1;
    lcd.setCursor(8,1); 
    lcd.print(OrangeCount); 
  }
  if(R<300 & R>240 & G<340 & G>280 & B<220 & B>180){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("    Purple");
     color = 2;
     PurpleCount = PurpleCount+1;
     lcd.setCursor(8,1);
     lcd.print(PurpleCount); 
  }
  if(R<250 & R>199 & G<280 & G>240 & B<260 & B>200){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("     Yellow");
    color = 3;
    YellowCount = YellowCount+1;
    lcd.setCursor(8,1); 
    lcd.print(YellowCount); 
  }
  if(R<300 & R>260 & G<310 & G>260 & B<250 & B>200){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("     Green");
    color = 4; 
    GreenCount = GreenCount+1;
    lcd.setCursor(8,1); 
    lcd.print(GreenCount); 
  }
  if(R>300 & G>300 & B>220){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("   No Object");
    lcd.setCursor(0,1);
    lcd.print("    Detected");
    delay(3000);
    lcd.clear();
  }
return color;  
}
