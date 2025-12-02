This project utilizes an Arduino and an L298N motor driver to control a 4-wheel drive chassis. It is controlled via a Smartphone Bluetooth App.

Key improvements in this version:

Safety Guard: The car automatically stops if an obstacle is detected within 20cm. It also refuses "Forward" commands until the path is clear.

Glitch Fix: The Ultrasonic Echo pin has been moved to Pin A4 to avoid the common LED built-in interference (Pin 13 glitch) often found on Arduino Unos.

Feedback: Active buzzer alerts for obstacles and startup.

🛠️ Hardware Requirements
Microcontroller: Arduino Uno (or Nano/Mega)

Motor Driver: L298N H-Bridge Module

Motors: 4x DC Gear Motors + Wheels

Communication: HC-05 or HC-06 Bluetooth Module

Sensors: HC-SR04 Ultrasonic Sensor

Actuators: SG90 Servo Motor (for sensor mounting)

Audio: Active Buzzer

Note on Analog Pins: This code uses Analog pins (A0-A4) as Digital Outputs/Inputs to save standard digital pins for PWM and communication.

Power: 2x Li-ion 18650 Batteries (or 9V/12V equivalent power source)

Misc: Jumper wires, Chassis

🧩 Software & Libraries
This code uses standard libraries included with the Arduino IDE. No external downloads are required.

Servo.h - For controlling the servo motor.

SoftwareSerial.h - For Bluetooth communication on pins 10 & 11.

🚀 Installation & Setup
Assembly: Mount motors to chassis and wire connections according to the table above.

Arduino IDE: Open the .ino file.

Upload: Connect your Arduino via USB. Select the correct Board and Port, then click Upload.

Note: You usually do not need to unplug the HC-05 while uploading because we are using SoftwareSerial (Pins 10/11) instead of Hardware Serial (0/1).

Power Up: Turn on the battery power. You should hear a startup beep sequence (Beep-Beep).

Connect: Open your Bluetooth app, pair with your HC-05 (Default password is usually 1234 or 0000), and connect.

⚠️ Troubleshooting
Car won't move forward: Check if the Ultrasonic sensor is blocked. The code prevents forward movement if distance < 20cm.

Bluetooth not connecting: Ensure the RX pin of the Bluetooth module connects to Pin 11 (TX) of Arduino, and TX of Bluetooth connects to Pin 10 (RX) of Arduino.

Servo Jitter: Ensure the power supply provides enough current. Servos and Motors sharing the Arduino 5V pin can cause resets; it is better to power the L298N directly from the battery.

Wirings:
<img width="471" height="321" alt="image" src="https://github.com/user-attachments/assets/3ef10a63-92b6-4c4f-af99-858c47c71b64" />
