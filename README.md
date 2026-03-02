# 📟 Arduino RFID Door Lock
## An RFID-based access control system developed with Arduino UNO R3 board

This project features an automated, secure access control system powered by an Arduino UNO R3 board. It uses RFID technology to verify authorized tags, controlling a mechanical door lock with a servo motor. The system provides comprehensive feedback through an LCD display, LED indicators, and a buzzer, offering a modern, contactless alternative to traditional key-based locks.<br>

The system uses an RFID reader to scan cards/tags, comparing the scanned unique identifier (**UID**) with a value stored in the program's memory. Depending on the card's validity, the Arduino microcontroller coordinates the physical opening of the lock and provides visual (via LCD and LEDs) and audible (via buzzer) feedback.<br><br>

## ⚙️ Components
The following components were used to build the system:
* **`Arduino UNO R3`**: Development board (system's central unit).
* **`RFID RC522 Module`**: Card/tag scanning module.
* **`16x2 LCD Display with I2C converter`**: Screen for displaying status messages; uses the I2C converter to communicate with the development board.
* **`Active Buzzer`**: Used to generate audible warning signals.
* **`SG90 Servo Motor`**: Precision motor used for mechanical actuation of the lock (pulling/releasing the mechanical bolt, corresponding to open/closed states).
* **`Mechanical Bolt`**: Metal bolt used to simulate the actual door locking/unlocking mechanism.
* **`Copper Wire`**: Used to connect the bolt to the servo motor arm.
* **`3mm Red LED`**: Used to indicate access denial.
* **`3mm Green LED`**: Used to indicate the unlocking of the bolt and access permission.
* **`2 Carbon Resistors, 220Ω, 0.25W`**: Used to limit current intensity to avoid burning out the LEDs.
* **`Capacitor, 220 μF, 10V`**: Used to stabilize voltage during sudden current consumption by the servo motor (at startup).
* **`Male-to-male and female-to-male Dupont wires`**: Used for interconnecting the circuit components.
* **`Breadboard (prototyping board)`**: Used for quick component interconnection without soldering, allowing for power distribution (5V and GND) to multiple devices simultaneously, as well as mounting the resistors, LEDs, and the capacitor in the circuit.
* **`USB Type-A to Type-B Cable`**: Provides dual functionality: powering the circuit with a constant 5V voltage from a computer and transferring the source code from the development environment (Arduino IDE) to the microcontroller's Flash memory.
* **`Plexiglass Support (4mm thickness)`**: Used for rigid mounting of all components, ensuring structural stability of the system.

<div align="center">
  <img width="700" height="600" alt="image" src="https://github.com/user-attachments/assets/d3ba04ff-025d-4cd7-96f1-be6a7706574d" />
</div><br><br>

## 🔧 Software Implementation
The software implementation consists of two distinct programs designed to manage the identification and access logic of the system:
* **`ScanUID.ino`** - This program is designed to extract the UID from the RFID tag. It initializes the SPI protocol, the RFID reader, and the LCD display to output the tag's hexadecimal code, allowing the user to identify and record the authorization key.

<div align="center">
  <img width="327" height="116" alt="image" src="https://github.com/user-attachments/assets/4746764c-7080-4c42-ab00-9e2250adc5b6" /><br><br>
  <img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/2ee0d584-9d4e-4f4f-baa1-c295585df9c7" /><br><br>
  <img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/6965cf5a-379c-4f69-8cc7-1d55f2502f92" />
</div><br><br>

* **`proiect.ino`** (Access Control Logic): This is the core program that coordinates hardware components to regulate access. It uses a predefined constant for the authorization UID and specific servo angles to control the mechanical locking mechanism (70° for locked, 120° for unlocked). The program continuously monitors for a new card , validates the scanned tag against the stored ID, and triggers specific feedback: granting access (green LED, confirmation beep, and unlocking) or denying entry (red LED, alarm sequence, and keeping the door locked).

<div align="center">
  <img width="352" height="133" alt="image" src="https://github.com/user-attachments/assets/49c808f4-58aa-4b52-8514-7be143fc6803" /><br><br>
  <img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/353837e9-b010-4175-ab21-2e6ca1ff02e0" /><br><br>
  <img width="600" height="500" alt="image" src="https://github.com/user-attachments/assets/370a7d51-4b04-4d46-8780-cc0a49754529" />
</div><br><br>

The system uses the following libraries to ensure seamless hardware integration:
* **`MFRC522.h`**: For RFID module control and data decoding.
* **`LiquidCrystal_I2C.h`**: For controlling the display via the I2C interface.
* **`Servo.h`**: For precise control of the locking mechanism.
* **`SPI.h`**: For reliable communication between the Arduino board and the RFID module.<br><br>

## 📘 Usage Guide
This section outlines how to operate the system and interpret its feedback signals:
* **`Startup & Standby`**: Connect the system to a 5V power source via USB. Upon startup, the latch automatically locks (70°), and the LCD displays a welcome message. In standby, the LEDs remain off, and the buzzer is inactive.
* **`Scanning Procedure`**: Hold your RFID card or tag 1–3 cm away from the MFRC522 antenna. The LCD will display "Scanning..." along with progress indicators while the UID is processed.
* **`Access Granted`**: If an authorized card is detected, the green LED lights up, the buzzer emits a short confirmation beep, and the servo rotates to 120°, opening the lock for 10 seconds before automatically re-locking.
* **`Access Denied`**: If an unknown card is used, the red LED lights up, and the buzzer emits a rapid 3-beep alarm. The lock remains closed (70°), and the system resets after 2 seconds.
* **`Troubleshooting`**: If the system fails to react, ensure the card is held parallel to the reader. You can use the **Serial Monitor** to debug and view the hexadecimal codes of scanned tags in real-time.<br><br>

## 🚀 Potential Improvements
While this system functions as a reliable prototype, there are several ways to improve the project for real-world applications and increased security:
* **`Improving Authorization`** - Currently, the system uses a single hardcoded UID for access. Using the board's internal EEPROM would allow the user to add or remove multiple authorized tags without modifying the source code.
* **`IoT Connectivity`**: Integrate a Wi-Fi (e.g., ESP8266 or ESP32) or Bluetooth module to receive real-time notifications on a smartphone whenever the door is opened or if an unauthorized access attempt is detected.
* **`PCB Prototyping`**: While the breadboard is good for development, designing a custom printed circuit board (PCB) would make the system more compact, durable, and suitable for permanent installation on an actual door.
* **`Independent Power Supply`**: Currently, the system requires a USB connection for 5V power. Integrating a lithium battery with a charging module would allow the lock to function independently of a computer or wall outlet.
* **`Enhanced Security`**: The current system relies solely on RFID. Adding multi-factor authentication, such as a physical keypad for a PIN or a fingerprint sensor would significantly increase the security level.
* **`Access Logging`**: Adding an SD card module would allow the system to maintain a local log file, recording the timestamp and UID of every successful or failed access attempt for security auditing.
