/* Arduino-RFID-Door-Lock */

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define GREEN_LED 5
#define RED_LED 6
#define BUZZER 8

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

String UID = "66 37 57 B8";  // UID-ul corect al tag-ului pentru acces

// pozitiile servomotorului (incuietoare inchisa/deschisa)
const int lockedAngle = 70;
const int unlockedAngle = 120;

void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // stare initiala: LED-uri stinse, buzzer oprit
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, HIGH);

  // initializare servomotor
  servo.attach(3);
  servo.write(lockedAngle);

  // initializare LCD
  lcd.init();
  lcd.backlight();

  // initializare modul RFID si protocolul SPI
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  // mesajul initial de asteptare pentru scanare card
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Scan your card");

  if (!rfid.PICC_IsNewCardPresent()){
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Error: Card detected but unable to read data!");
    return;
  }

  // se citeste UID-ul cardului
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is:");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    delay(300);
  }
  Serial.println();
  ID.toUpperCase();

  // logica de acces
  if (ID.substring(1) == UID) { // card corect
    digitalWrite(GREEN_LED, HIGH);

    // un scurt beep de confirmare acces
    digitalWrite(BUZZER, LOW);
    delay(200);
    digitalWrite(BUZZER, HIGH);

    // deschidere incuietoare
    servo.write(unlockedAngle);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Access Granted");
    lcd.setCursor(2, 1);
    lcd.print("Door is open");

    delay(10000);  // incuietoarea ramane deschisa 10 secunde pentru a permite accesul

    servo.write(lockedAngle); // inchidere incuietoare dupa ce au trecut cele 10 secunde
    digitalWrite(GREEN_LED, LOW);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Door locked");
    delay(2000);
    lcd.clear();
  } 
  else { // card gresit
    digitalWrite(RED_LED, HIGH);

    // alarma: 3 beep-uri rapide
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER, LOW);  // alarma suna
      delay(100);
      digitalWrite(BUZZER, HIGH);  // alarma se opreste
      delay(100);
    }

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Wrong card!");
    delay(1000);

    servo.write(lockedAngle);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    lcd.clear();
  }
}