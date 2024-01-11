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
    setPos(4, 86);
    delay(500);
    setPos(8, 180);
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
    setPos(11, 150);
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
