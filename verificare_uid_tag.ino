#include <SPI.h>
#include <MFRC522.h>
// pinii de la RFID
#define RST_PIN   42      
#define SS_PIN    53    

MFRC522 rfid(SS_PIN, RST_PIN);  // Inițializează modulul MFRC522

void setup() {
  Serial.begin(9600); // Inițializează comunicarea serială
  SPI.begin();        // Inițializează SPI
  rfid.PCD_Init();    // Inițializează modulul MFRC522
  Serial.println("Apropiati un tag RFID pentru a afla UID-ul.");
}

void loop() {
  // Verifică dacă un card este prezent
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    //seria cardului
    MFRC522::Uid uid = rfid.uid;
    
    // Afișează seria cardului în format hexazecimal
    Serial.print("UID: ");
    for (byte i = 0; i < uid.size; i++) {
      Serial.print(uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(uid.uidByte[i], HEX);
    }
    Serial.println();
    
    rfid.PICC_HaltA(); // Oprește comunicarea cu cardul
  }
}
