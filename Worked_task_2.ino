#include <avr/power.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver Ada = Adafruit_PWMServoDriver();

//Ultrasonic1
#define echo_1 8  //Left white
#define trig_1 9  //Left purple
//ultrasonic2
#define echo_2 3  //Right brown
#define trig_2 2  //Right white

#define TRIG_1_BIT (1 << (trig_1 - 8))  // Adjust for port bit
#define TRIG_2_BIT (1 << (trig_2 - 8))  // Adjust for port bit

#define servoMAX 600
#define servoMIN 150

// Constrains
const int maxdist = 200;
const int mindist = 5;
//distance initiate
unsigned long previousMillis = 0;

void nonBlockingDelay(int interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Reset the timer
    previousMillis = currentMillis;
  }
}

inline void setPos(int servo, int angle) {
  // Map angle to pulse width (0,180) --> (150,600)
  int pulseWidth = map(angle, 0, 180, servoMIN, servoMAX);

  // Set the on and off times for the PCA9685
  Ada.setPWM(servo, 0, pulseWidth);
}

void stand_instantly() {
  setPos(0, 75);
  nonBlockingDelay(500);
  setPos(4, 84);
  nonBlockingDelay(500);
  setPos(8, 170);
  nonBlockingDelay(500);
  setPos(1, 92);
  nonBlockingDelay(500);
  setPos(5, 90);
  nonBlockingDelay(500);
  setPos(9, 137);
  nonBlockingDelay(500);
  setPos(2, 85);
  nonBlockingDelay(500);
  setPos(6, 92);
  nonBlockingDelay(500);
  setPos(10, 165);
  nonBlockingDelay(500);
  setPos(3, 80);
  nonBlockingDelay(500);
  setPos(7, 85);
  nonBlockingDelay(500);
  setPos(11, 140);
  nonBlockingDelay(500);
  //Serial.println("Stand up: complete");
}

float readUltrasonic(byte trig, byte echoPin) {
  int duration;
  switch (trig) {
    case 1:
      digitalWrite(trig_1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_1, LOW);
      delayMicroseconds(2);
      duration = pulseIn(echoPin, HIGH);
      //Serial.println(duration);
      return (duration * 172L) / 10000;
      break;
    case 2:
      digitalWrite(trig_2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_2, LOW);
      delayMicroseconds(2);
      duration = pulseIn(echoPin, HIGH);
      //Serial.println(duration);
      return (duration * 172L) / 10000;
      break;
  }
}

void legExtend(int distance1, int distance2) {
  if (distance2 < 35 && distance2 > 10) {
    setPos(7, 75);
    setPos(11, 40);
    delay(5000);
    stand_instantly();
    delay(400);
  } else if (distance1 < 35 && distance1 > 10) {
    setPos(5, 75);
    setPos(9, 40);
    delay(5000);
    stand_instantly();
    delay(400);
  }
}

void setup() {
  //DDRB |= TRIG_1_BIT | TRIG_2_BIT;  // Set trigger pins as outputs
  pinMode(trig_1, OUTPUT);
  pinMode(echo_1, INPUT);
  pinMode(trig_2, OUTPUT);
  pinMode(echo_2, INPUT);
  //power_twi_disable();
  power_spi_disable();
  //Serial.begin(115200);
  Ada.begin();
  Ada.setPWMFreq(60);
  stand_instantly();
  delay(3000);
}

void loop() {
  int distance1 = readUltrasonic(1, echo_1);
  //Serial.print("Distance1: ");
  //Serial.println(distance1);
  int distance2 = readUltrasonic(2, echo_2);
  //Serial.print("Distance2: ");
  //Serial.println(distance2);
  legExtend(distance1, distance2);
  //delay(300);
}
