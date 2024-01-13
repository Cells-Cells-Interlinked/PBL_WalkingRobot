#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Servo.h>

Adafruit_PWMServoDriver Ada = Adafruit_PWMServoDriver();

#define servoMAX 600
#define servoMIN 150

void setPos(int servo,int angle) {
    // Map angle to pulse width (0,180) --> (150,600)
    int pulseWidth = map(angle, 0, 180, servoMIN, servoMAX);

    // Set the on and off times for the PCA9685
    Ada.setPWM(servo, 0, pulseWidth);
}

void stand(){
    setPos(0, 75);
    delay(500);
    setPos(4, 84);
    delay(500);
    setPos(8, 170);
    delay(500); 
    setPos(1, 92);
    delay(500);
    setPos(5, 90);
    delay(500);
    setPos(9, 137);
    delay(500); 
    setPos(2, 85);
    delay(500);
    setPos(6, 92);
    delay(500); 
    setPos(10, 165);
    delay(500);
    setPos(3, 80);
    delay(500);
    setPos(7, 85);
    delay(500); 
    setPos(11, 140);
    delay(500);
    Serial.println("Stand up: complete");
}

void test2(){
  Serial.println("initiate the sequence");
  setPos(9, 40);
  delay(500);
  setPos(0, 55);
}

void stable(){
    setPos(8, 110);
    setPos(4, 25);
    delay(500);
    setPos(10, 95);
    setPos(6, 36);
    delay(500);
    setPos(9, 85);
    setPos(5, 27);
    delay(500);
    setPos(11, 85);
    setPos(7, 38);
    delay(500);
}

void linear(){
    setPos(0, 45);
    setPos(2, 65);
    setPos(1, 115);
    setPos(3, 100);
    delay(500);
}

void step1(){
    setPos(3, 100);
    setPos(1, 65);
    delay(700);
    setPos(4, 120);
    setPos(8, 120);
    delay(700);
    setPos(0, 45);
    delay(500);
    setPos(4, 60);
    delay(700);
    setPos(2, 105);
    setPos(1, 92);
    setPos(3, 100);
    delay(1000);
    setPos(7, 140);
    setPos(11, 120);
    delay(500);
    setPos(7, 85);
    delay(700);
    setPos(1, 110);
    setPos(2, 55);
    delay(700);
    setPos(9, 117);
    setPos(10, 145);
    setPos(5, 70);
    setPos(6, 80);
    setPos(8, 120);
    setPos(11, 140);
    delay(1000);
//    setPos(5, 50);
//    setPos(6, 60);
//    setPos(9, 100);
//    setPos(10, 130);
//    setPos(0, 75);
//    setPos(3, 80);
//    delay(1000);
//    setPos(2, 105);
//    setPos(3, 60);
//    delay(500);
//    setPos(8, 140);
//    setPos(7, 65);
//    setPos(10, 155);
//    delay(500);
//    setPos(6, 60);
//    setPos(5, 60);
//    setPos(6, 60);

    Serial.println("motion completed");
}

void step2(){
    setPos(3, 100);
    setPos(1, 65);
    delay(700);
    setPos(4, 120);
    setPos(8, 120);
    delay(700);
    setPos(0, 45);
    delay(500);
    setPos(4, 60);
    delay(700);
    setPos(1, 110);
    setPos(3, 60);
    setPos(10, 145);
    setPos(8, 155);
    delay(1000);

    setPos(2, 105);
    setPos(10, 160);
    delay(700);
    setPos(6, 50);
    setPos(10, 140);
    delay(1000);

//    setPos(7, 105);
//    delay(500);
//    setPos(3, 100);
//    delay(700);
//    setPos(7, 120);
//    setPos(11, 120);
//    delay(700);
//    setPos(7, 60);
//    delay(500);
//    setPos(0, 90);
//    setPos(2, 55);
//    setPos(9, 125);
//    setPos(11, 155);
    
}

//End of Functions

void setup() {
  Serial.begin(9600);
  Ada.begin();
  Ada.setPWMFreq(60);
  stand();
//  stable();
}

void loop() {
  if (Serial.available() > 0) {
    // Read the integers from serial
    int serNum = Serial.parseInt();
    
    // Check if there's a space before reading the second integer
    if (Serial.read() == ' ') {
      int degVal = Serial.parseInt();

    Serial.print(serNum);
    Serial.print(' ');
    Serial.println(degVal);

      // Perform tasks based on the received integers
      switch (serNum) {
        case 12:
          stand();
          break;

        case 13:
          linear();
          break;

        case 14:
          step2();
          break;
          
        default:
          // Code to handle invalid or unrecognized values of the first integer
          setPos(serNum, degVal);
          break;
      }
    }
  }
}
