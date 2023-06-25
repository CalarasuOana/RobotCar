#include <SoftwareSerial.h>
SoftwareSerial BTserial(19, 18);//(RX,TX) portul secundar 
char c = '0';
const int MotorRight1 = 7;  // IN1
const int MotorRight2 = 8;  // IN2
const int MotorLeft1 = 9;   // IN3
const int MotorLeft2 = 10;  // IN4
const int MotorRightPWM = 6; // ENA
const int MotorLeftPWM = 11; // ENB
int iSpeed = 220; //viteza maxima setata a robotului mobil
void setup()
{
  Serial.begin(9600); //viteza de transmisie 9600
  Serial1.begin(9600);
  //setare pini motor 
  pinMode(MotorRight1, OUTPUT);
  pinMode(MotorRight2, OUTPUT);
  pinMode(MotorLeft1, OUTPUT);
  pinMode(MotorLeft2, OUTPUT);
  pinMode(MotorRightPWM, OUTPUT);
  pinMode(MotorLeftPWM, OUTPUT);

  Serial.println("HC-05 a fost pornit cu succes");
}

void loop()
{
  if (Serial1.available())
  {
    c = Serial1.read();
    Serial.write(c);
    if (c == 'S') //primire comanda buton INAINTE
    {
      straight(50);
    }
    else if (c == 'R')  //primire comanda buton DREAPTA
    {
      turnright(10);
    }
    else if (c == 'P')  //primire comanda buton GARARE
    {
      backparking();
    }
    else if (c == 'B') // //primire comanda buton INAPOI
    {
      back(10);
    }
    else if (c == 'X')  //primire comanda buton STOP
    {
      stopp(10);
    }
    else if (c == 'L')  //primire comanda buton STANGA
    {
      turnleft(10);
    }
     else if (c == 'T')  //primire comanda buton PARCARE LATERALA
    {
      lateralparking();
    }
  }
 //verificare existenta date disponibile pentru citire din portul serial
  if (Serial.available())
  {
    c = Serial.read(); //se citeste caracterul c din portul serial
    Serial1.write(c); //se trimite caracterul c catre portul secundar
  }
}

void straight(int d)//inainte
{ 
  digitalWrite(MotorRight1, HIGH);
  digitalWrite(MotorRight2, LOW);
  digitalWrite(MotorLeft1, HIGH);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
  Serial.println("Mergi înainte");
}

void turnright(int d)//dreapta
{ 
  digitalWrite(MotorLeft1, HIGH);
  digitalWrite(MotorLeft2, LOW);
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

void turnleft(int d) //stanga
{ 
  digitalWrite(MotorRight1, HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}
void turnleftback(int d) //virare stanga spate
{ 
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

void turnrightback(int d) //virare dreapta spate 
{ 
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, HIGH);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

void stopp(int d) //stop
{ 
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, LOW);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

void back(int d) //inapoi
{ 
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, HIGH);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, HIGH);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}


void backparking() { //garare
turnleftback(500);
    delay(500); 
    back(120);
    delay(1000); 
    stopp(1);
}

void lateralparking() { //parcare laterala
    turnleftback(90);
    delay(1500);
    back(30);
    delay(500);
    turnrightback(50);
    delay(500);
    back(30);
    delay(500);
    stopp(1);
}
