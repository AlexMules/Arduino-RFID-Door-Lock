/* programul pentru aflarea codului UID al unui card de acces */
 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10
byte readCard[4]; // array pentru stocarea celor 4 octeti ai UID-ului
byte columnPos = 0; // variabila pentru afisare pe display LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  while (!Serial){ // asteptare pana la deschiderea portului serial 
    ;
  }

  // initializare modul RFID si protocolul SPI
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println();

  lcd.setCursor(1, 0);
  lcd.print("Scan your card");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanned UID");

  // bucla pentru citirea codului UID al cardului de acces
  columnPos = 0;
  Serial.println(F("Scanned PICC's UID:"));
  for (uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
    Serial.print(" ");
    lcd.setCursor(columnPos, 1);
    lcd.print(readCard[i], HEX);
    lcd.print(" ");
    delay(500);
    columnPos += 3;
  }
  Serial.println("\n");
  mfrc522.PICC_HaltA();
  return;
}