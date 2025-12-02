/*
 * 4-Wheel Robot Car - FINAL STABLE VERSION
 * * FIXES: 
 * - Moved Echo to A4 to prevent "3cm" glitch on Pin 13
 * - Auto-Stop on obstacle
 * - Servo Scanning
 * * * WIRING:
 * L298N IN1 --> Arduino A0
 * L298N IN2 --> Arduino A1
 * L298N IN3 --> Arduino A2
 * L298N IN4 --> Arduino A3
 * Buzzer    --> Pin 8
 * Servo     --> Pin 9
 * HC-05 TX  --> Pin 10
 * HC-05 RX  --> Pin 11
 * Ultrasonic Trig --> Pin 12
 * Ultrasonic Echo --> Pin A4  <-- CHANGED THIS
 */

#include <Servo.h>
#include <SoftwareSerial.h>

// --- PINS ---
const int IN1 = A0; 
const int IN2 = A1;
const int IN3 = A2;
const int IN4 = A3;

SoftwareSerial BTSerial(10, 11); // RX, TX

Servo myServo;
const int servoPin = 9;
const int trigPin = 12;
const int echoPin = A4; // NEW PIN
const int buzzerPin = 8;

// --- VARIABLES ---
char command;
long duration;
int distance = 100; 
const int stopDist = 20; // Stop distance in cm
unsigned long lastCheckTime = 0;

void setup() {
  // Motor Pins
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  // Sensors
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); // A4 used as Input
  pinMode(buzzerPin, OUTPUT);

  // Servo
  myServo.attach(servoPin);
  myServo.write(90); 
  delay(500); 

  Serial.begin(9600);
  BTSerial.begin(9600);
  
  // Startup Beeps
  beep(100); delay(100); beep(100);
}

void loop() {
  // 1. CHECK SENSOR (Every 100ms)
  if (millis() - lastCheckTime > 100) {
    checkObstacles();
    lastCheckTime = millis();
  }

  // 2. CHECK BLUETOOTH
  if (BTSerial.available()) {
    command = BTSerial.read();
    executeCommand(command);
  }
}

void executeCommand(char cmd) {
  // SAFETY GUARD: Refuse 'F' if blocked
  if (cmd == 'F' && distance > 0 && distance < stopDist) {
    stopCar();
    beep(50); 
    return; 
  }

  switch (cmd) {
    case 'F': 
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      break;
      
    case 'B': 
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      break;

    case 'L': 
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      break;

    case 'R': 
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      break;

    case 'S': stopCar(); break;
    case 'V': beep(300); break;
  }
}

void checkObstacles() {
  // Read Ultrasonic
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10); digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Filter out "0" errors and detect real obstacles
  if (distance > 2 && distance < stopDist) {
    digitalWrite(buzzerPin, HIGH);
    stopCar(); 
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void beep(int time) {
  digitalWrite(buzzerPin, HIGH); delay(time); digitalWrite(buzzerPin, LOW);
}