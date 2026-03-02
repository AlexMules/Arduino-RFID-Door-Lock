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
* **`Plexiglass Support (4mm thickness)`**: Used for rigid mounting of all components, ensuring structural stability of the system.<br><br>


