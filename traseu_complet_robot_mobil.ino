#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// pinii de la RFID
#define SS_PIN 53
#define RST_PIN 42
//OLED
#define OLED_ADDR   0x3C // Adresa I2C a display-ului OLED
#define OLED_SDA    20  // Pinul SDA conectat la Arduino
#define OLED_SCL    21  // Pinul SCL conectat la Arduino

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(-1);

const int MotorRight1 = 7;   // IN1
const int MotorRight2 = 8;   // IN2
const int MotorLeft1 = 9;    // IN3
const int MotorLeft2 = 10;   // IN4
const int MotorRightPWM = 6; // ENA
const int MotorLeftPWM = 11; // ENB
//senzor ultrasonic plasat in stanga
const int trigPin2 = 30;  // Pinul de trimitere semnal către senzorul (TRIG)
const int echoPin2 = 31;  // Pinul de recepție semnal de la senzor (ECHO)
//senzor ultrasonic plasat in fata
const int trigPin1 = 37;  // Pinul de trimitere semnal către senzor (TRIG)
const int echoPin1 = 36;  // Pinul de recepție semnal de la senzor (ECHO)
int iSpeed = 250; //viteza maxima setata a robotului
int iSpeed1 = 10;
int iSpeed2 = 5;
int iSpeed3 = 0;
int valid = 1;

// senzorii de linie
int lineSensor8 = A8;
int lineSensor7 = A9;
int lineSensor6 = A10;
int lineSensor5 = A11;
int lineSensor4 = A12;
int lineSensor3 = A13;
int lineSensor2 = A14;
int lineSensor1 = A15;
bool tagDetected = false; // Variabilă de stare pentru a urmări dacă tag-ul a fost detectat

void setup() {
  Serial.begin(9610);
  pinMode(MotorRight1, OUTPUT);
  pinMode(MotorRight2, OUTPUT);
  pinMode(MotorLeft1, OUTPUT);
  pinMode(MotorLeft2, OUTPUT);
  pinMode(MotorRightPWM, OUTPUT);
  pinMode(MotorLeftPWM, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  SPI.begin();
  rfid.PCD_Init();
  //folositi pentru motoare
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Wire.begin(); // initializarea conexiunii I2C cu display-ul OLED
   
      if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
             Serial.println(F("Eroare la inițializarea display-ului OLED"));
              while (1);
       }

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
}
String uidToString(MFRC522::Uid uid) { //stocarea seriei tag-ului
  String uidString = ""; 
  //parcurgerea fiecarui byte
  for (byte i = 0; i < uid.size; i++) {
    if (uid.uidByte[i] < 0x10) {
      //convertirea in string
      uidString += "0";
    }
    uidString += String(uid.uidByte[i], HEX);
    uidString.toUpperCase();
    //se adauga un spatiu dupa valoarea hexazecimala a  byte-ului
    if (i < uid.size - 1) {
      uidString += " ";
    }
  }
  return uidString;
}

void loop() {
  if (!tagDetected) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Card ");
    display.println("nedetectat");
    display.display();
    stopp(1); // Mașinuța stă pe loc până când detectează card-ul

    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      // Obține seria cardului
      MFRC522::Uid uid = rfid.uid;

      // Verifică uid-ului
      if (uidToString(uid) == "C1 9F 16 24") {
        // Afișarea mesajului pe afișajul OLED
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Card ");
        display.println("detectat");
        display.display();
        tagDetected = true; // Setează variabila de stare ca fiind adevărată
        delay(1000);
      }
    }
  } else {
    // Restul logicii pentru urmărirea mașinii
    straight(5);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Urmareste linia");
    display.display();
       
    // urmarirea masinii
    /*long distance2 = getDistanceFromFrontSensor();
    Serial.print("Distance from front sensor: ");
    Serial.print(distance2);
    Serial.println(" cm");
      display.setCursor(0, 0); 
      display.clearDisplay();
      display.println("Urmareste masina");
      display.display();
   */
    int sensorValue1 = analogRead(lineSensor1);
    int sensorValue2 = analogRead(lineSensor2);
    int sensorValue3 = analogRead(lineSensor3);
    int sensorValue4 = analogRead(lineSensor4); 
    int sensorValue5 = analogRead(lineSensor5);
    int sensorValue6 = analogRead(lineSensor6);
    int sensorValue7 = analogRead(lineSensor7);
    int sensorValue8 = analogRead(lineSensor8);

    //trebuie comentat daca se doreste urmarirea masinii
    //merge inainte daca senzorii din mijloc detecteaza linia neagra
    if (sensorValue5 > 760 || sensorValue4 > 760) {
      straight(5);
    }
        if (sensorValue8 > 760) { //vireaza mult stanga (primul senzor din stanga)
          digitalWrite(MotorRight1, HIGH);
          digitalWrite(MotorRight2, LOW);
          digitalWrite(MotorLeft1, HIGH);
          digitalWrite(MotorLeft2, LOW);
          analogWrite(MotorRightPWM, iSpeed);
          analogWrite(MotorLeftPWM, iSpeed3);
        }
        if (sensorValue7 > 760) {
          digitalWrite(MotorRight1, HIGH);
          digitalWrite(MotorRight2, LOW);
          digitalWrite(MotorLeft1, HIGH);
          digitalWrite(MotorLeft2, LOW);
          analogWrite(MotorRightPWM, iSpeed);
          analogWrite(MotorLeftPWM, iSpeed2);
        }
        if (sensorValue6 > 760) {
          digitalWrite(MotorRight1, HIGH);
          digitalWrite(MotorRight2, LOW);
          digitalWrite(MotorLeft1, HIGH);
          digitalWrite(MotorLeft2, LOW);
          analogWrite(MotorRightPWM, iSpeed);
          analogWrite(MotorLeftPWM, iSpeed1);
        }
        if (sensorValue3 > 760) {
          digitalWrite(MotorRight1, HIGH);
          digitalWrite(MotorRight2, LOW);
          digitalWrite(MotorLeft1, HIGH);
          digitalWrite(MotorLeft2, LOW);
          analogWrite(MotorRightPWM, iSpeed);
          analogWrite(MotorLeftPWM, iSpeed1);
        }
        if (sensorValue2 > 760) {
          digitalWrite(MotorRight1, HIGH);
          digitalWrite(MotorRight2, LOW);
          digitalWrite(MotorLeft1, HIGH);
          digitalWrite(MotorLeft2, LOW);
          analogWrite(MotorRightPWM, iSpeed);
          analogWrite(MotorLeftPWM, iSpeed2);
        }
        if (sensorValue1 > 760) {    // vireaza mult dreapta (primul senzor din dreapta)
          digitalWrite(MotorRight1, HIGH);
          digitalWrite(MotorRight2, LOW);
          digitalWrite(MotorLeft1, HIGH);
          digitalWrite(MotorLeft2, LOW);
          analogWrite(MotorRightPWM, iSpeed);
          analogWrite(MotorLeftPWM, iSpeed3);
        }
      // comentat pana aici

    //afisarea valorilor senzorilor
    Serial.print(sensorValue1);
    Serial.print(" ");
    Serial.print(sensorValue2);
    Serial.print(" ");
    Serial.print(sensorValue3);
    Serial.print(" ");
    Serial.print(sensorValue4);
    Serial.print(" ");
    Serial.print(sensorValue5);
    Serial.print(" ");
    Serial.print(sensorValue6);
    Serial.print(" ");
    Serial.print(sensorValue7);
    Serial.print(" ");
    Serial.print(sensorValue8);
    Serial.print(" ");
    Serial.println();
        
    int distance1 = getDistanceFromLeftSensor();
        if (distance1 < 10 && distance1 >=5) {
          backparking(); // Realizeaza backparking atunci cand distanta este intre 10 si 5
          stopp(5);
           } 
     }
    
  }
  

void backparking() {
 //Manevrele pentru a face parcarea cu spatele
  turnleft(400); // virare stanga timp de 0.4 secunde
  delay(750); //intarziere de 0.7 secunde
  back(50);//deplasare inapoi
  delay(500);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Back");
    display.println("parking");
    display.display(); // afiseaza textul„Back parking” pe display-ul OLED
  stopp(300);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Coboara");
    display.println("pasageri");
    display.display();//afiseaza textul „Coboara pasageri” pe OLED
  delay(4000);//timpul de asteptare pentru a cobori pasagerii
    display.clearDisplay();
  back(50);//deplasare inapoi
  delay(50);
  //in continuare parcheaza in spatele cladirii
  lateralbackparking();
}

void lateralbackparking() {
 //afisarea pe OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Parking");
    display.display();
  //manevrele de parcare laterala cu spatele
  turnleft(200);//viraj la stanga
  delay(80);
  back(50);//deplasare inapoi
  delay(1000);
  turnright(40);//viraj la drapta
  delay(700);
  straight(50);//deplasare in linie dreapta
  delay(200);
  stopp(500);//oprire
  Serial.println("Parking");
}


void straight(int d) { //inainte
  digitalWrite(MotorRight1, HIGH);
  digitalWrite(MotorRight2, LOW);
  digitalWrite(MotorLeft1, HIGH);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
   Serial.println("Mergi înainte");
}

void turnright(int d) { //dreapta
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, HIGH);
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

void turnleft(int d) { //stanga
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, HIGH);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

void stopp(int d) { // stop
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, LOW);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
 
}

void back(int d) { // inapoi
  digitalWrite(MotorRight1, LOW);
  digitalWrite(MotorRight2, HIGH);
  digitalWrite(MotorLeft1, LOW);
  digitalWrite(MotorLeft2, HIGH);
  analogWrite(MotorRightPWM, iSpeed);
  analogWrite(MotorLeftPWM, iSpeed);
  delay(d * 10);
}

//senzor ultrasonic din 
long getDistanceFromLeftSensor() {
  // Trimiterea semnalului către senzor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Măsurarea timpului pentru semnalul de întoarcere (echo)
  long duration = pulseIn(echoPin1, HIGH);
  // Calcularea distanței în centimetri
  // Viteza sunetului în aer este de aproximativ 343,2 m/s sau 0,03432 cm/μs
  // Distanța = (timp * viteză) / 2
  long distance1 = (duration * 0.03432) / 2;
  // Afișarea valorii distanței și a valorii citite de la senzor
  Serial.print("Distanta de la senzorul din stanga: ");
  Serial.print(distance1);
  Serial.println(" cm");
  // Returnarea valorii distanței calculate
  return distance1;
}

//functia pentru urmarirea masinii aflate pe traseu
/*long getDistanceFromFrontSensor() {
  // Trimiterea semnalului către senzor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Măsurarea timpului pentru semnalul de întoarcere (echo)
  long duration = pulseIn(echoPin2, HIGH);

  // Calcularea distanței în centimetri
  // Viteza sunetului în aer este de aproximativ 343,2 m/s sau 0,03432 cm/μs
  // Distanța = (timp * viteză) / 2
  long distance2 = (duration * 0.03432) / 2;

  // Afișarea valorii distanței și a valorii citite de la senzor
  Serial.print("Distanta de la senzorul din: ");
  Serial.print(distance2);
  Serial.println(" cm");

        if (distance2>0 && distance2 < 13) {
          back(50); 
        } else if (distance2 > 13 && distance2 < 50) {
            straight(50); 
         } 
  // Returnarea valorii distanței calculate
  return distance2;
}
*/