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
    setPos(0, 95);
    delay(500);
    setPos(4, 90);
    delay(500);
    setPos(8, 140);
    delay(500); 
    setPos(1, 85);
    delay(500);
    setPos(5, 95);
    delay(500);
    setPos(9, 165);
    delay(500); 
    setPos(2, 80);
    delay(500);
    setPos(6, 95);
    delay(500); 
    setPos(10, 160);
    delay(500);
    setPos(3, 75);
    delay(500);
    setPos(7, 85);
    delay(500); 
    setPos(11, 167);
    delay(500);
    Serial.println("Stand up: complete");
}

//End of Functions//

void setup() {
    Serial.begin(9600);
    Ada.begin();
    Ada.setPWMFreq(60);
    stand();
}

void loop() {

}
