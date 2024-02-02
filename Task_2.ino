#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver Ada = Adafruit_PWMServoDriver();

//Ultrasonic1
#define echo_1 8 //Left white
#define trig_1 9 //Left purple
//ultrasonic2
#define echo_2 3 //Right brown
#define trig_2 2 //Right white

#define servoMAX 600
#define servoMIN 150

// Constrains
const int maxdist = 200;
const int mindist = 5;
//distance initiate
int distance_1, duration_1, distance_2, duration_2;
unsigned long previousMillis = 0;

void nonBlockingDelay(int interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Reset the timer
    previousMillis = currentMillis;
  }
}

void setPos(int servo,int angle) {
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
  Serial.println("Stand up: complete");
}

void usonic_transmit(int num) {
  switch(num){
    case 1:
      digitalWrite(trig_1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_1, LOW);
      delayMicroseconds(2);
      break;
    case 2:
      digitalWrite(trig_2,HIGH);
      delayMicroseconds(10);
      digitalWrite(trig_2, LOW);
      delayMicroseconds(2);
      break;
  }
}


void readUltrasonic(int num){
  switch(num){
    case 1:
      duration_1 = pulseIn(echo_1, HIGH);
      distance_1 = (duration_1*0.034)/2;

      Serial.print("Distance_1 :");
      Serial.print(distance_1);
      Serial.print(" ");

      // return distance_1;
      break;
    case 2:
      duration_2 = pulseIn(echo_2, HIGH);
      distance_2 = (duration_2*0.034)/2;

      Serial.print("Distance_2 :");
      Serial.print(distance_2);
      Serial.print("\n");

      // return distance_2;
      break;

  }
}

void leg_extend(){
      if(distance_2 < 50 && distance_2 > 10){
        setPos(7,75);
        setPos(11,40);
        delay(5000);
        stand_instantly();
      }
      else if(distance_1 < 50 && distance_1 > 10){
        setPos(5,75);
        setPos(9,40);
        delay(5000);
        stand_instantly();
      }
}

void setup(){
  pinMode(trig_1, OUTPUT);
  pinMode(echo_1, INPUT);
  pinMode(trig_2, OUTPUT);
  pinMode(echo_2, INPUT);
  Serial.begin(9600);
  Ada.begin();
  Ada.setPWMFreq(60);
  stand_instantly();
  delay(6000);
}

void loop(){
  //ultrasonic_1
  usonic_transmit(1);
  readUltrasonic(1);
  leg_extend();
  //ultrasonic_2
  usonic_transmit(2);
  readUltrasonic(2);
  leg_extend();


  //delay(300);
}
