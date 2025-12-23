/* Door lock system with Auto-Close
 * Modificat pentru LED-uri, Buzzer (ritm diferit) si Auto-Close
 */

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_VERDE 5
#define LED_ROSU 6
#define BUZZER 8

String UID = "66 37 57 B8";  // UID-ul tau corect

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

// Pozitiile servomotorului
int pozitie_inchis = 70;
int pozitie_deschis = 120;

void setup() {
  Serial.begin(9600);

  // Initializam pinii pentru LED-uri si Buzzer
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROSU, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Stare initiala: LED-uri stinse, Buzzer oprit (HIGH = Oprit pentru Low Trigger)
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROSU, LOW);
  digitalWrite(BUZZER, HIGH);

  // Initializam servo
  servo.attach(3);
  servo.write(pozitie_inchis);

  lcd.init();
  lcd.backlight();
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  // Mesajul de asteptare
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Scan your card");

  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Error: Card detected but unable to read data!");
    return;
  }

  // Citim UID-ul cardului
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
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

  // --- LOGICA DE ACCES ---

  if (ID.substring(1) == UID) {
    // --- CARD CORECT ---
    digitalWrite(LED_VERDE, HIGH);

    // Un singur beep scurt de confirmare (200ms)
    digitalWrite(BUZZER, LOW);
    delay(200);
    digitalWrite(BUZZER, HIGH);

    servo.write(pozitie_deschis);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Access Granted");
    lcd.setCursor(2, 1);
    lcd.print("Door is open");

    delay(10000);  // Usa ramane deschisa 10 secunde (LED-ul ramane aprins)

    servo.write(pozitie_inchis);
    digitalWrite(LED_VERDE, LOW);  // Stingem LED Verde dupa ce se inchide usa

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Door locked");
    delay(2000);
    lcd.clear();

  } else {
    // --- CARD GRESIT ---
    digitalWrite(LED_ROSU, HIGH);

    // Alarma: 3 beep-uri rapide (100ms pornit, 100ms oprit)
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER, LOW);  // Sună
      delay(100);
      digitalWrite(BUZZER, HIGH);  // Tace
      delay(100);
    }

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Wrong card!");
    delay(1000);

    servo.write(pozitie_inchis);
    delay(1000);  // Așteptăm restul timpului pentru ca utilizatorul să vadă mesajul
    digitalWrite(LED_ROSU, LOW);
    lcd.clear();
  }
}