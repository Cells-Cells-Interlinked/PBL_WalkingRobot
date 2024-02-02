#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver Ada = Adafruit_PWMServoDriver();

#define servoMAX 600
#define servoMIN 150

unsigned long previousMillis = 0;

void nonBlockingDelay(int interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Reset the timer
    previousMillis = currentMillis;
  }
}

void stand_instanly() {
  setPos(0, 75);
  nonBlockingDelay(500);
  setPos(4, 84);
  nonBlockingDelay(500);
  setPos(8, 160);
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
  setPos(11, 155);
  nonBlockingDelay(500);
  Serial.println("Stand up: complete");
}

inline void setPos(int servo,int angle) {
    // Map angle to pulse width (0,180) --> (150,600)
    int pulseWidth = map(angle, 0, 180, servoMIN, servoMAX);

    // Set the on and off times for the PCA9685
    Ada.setPWM(servo, 0, pulseWidth);
}

void creepwalk_up(int i,int r){
  //prep
  setPos(2, 105);
  setPos(3, 60);
  delay(200);
  //walking leg 4
  setPos(7,140);
  delay(200);
  setPos(3,100);
  delay(200);
  setPos(7, 55+i);
  setPos(11, 120+r);
  delay(200);
  setPos(3, 80);
  setPos(0, 90);
  setPos(1, 110);
  setPos(2, 55);
  delay(200);
  //walking leg2
  setPos(5, 130);
  delay(200);
  setPos(1 ,60);
  delay(200);
  setPos(5, 55-i);
  setPos(9, 100-r);
  delay(200);
  //walking leg1
  setPos(4, 135);
  delay(200);
  setPos(0, 40);
  delay(200);
  setPos(4, 55+i);
  setPos(8, 120+r);
  delay(200);
  setPos(0, 75);
  setPos(3, 60);
  setPos(1, 110);
  delay(200);
  //Preprep
  setPos(6, 140);
  delay(200);
  setPos(2, 105);
  delay(200);
  setPos(6, 55-i);
  setPos(10, 120-r-2);
}
void creepwalk_down(){
  //prep
  setPos(2, 105);
  setPos(3, 60);
  delay(200);
  //walking leg 4
  setPos(7,140);
  delay(200);
  setPos(3,100);
  delay(200);
  setPos(7, 85);
  setPos(11, 155);
  delay(200);
  setPos(3, 80);
  setPos(0, 90);
  setPos(1, 110);
  setPos(2, 55);
  delay(200);
  //walking leg2
  setPos(5, 130);
  delay(200);
  setPos(1 ,60);
  delay(200);
  setPos(5, 90);
  setPos(9, 165);
  delay(200);
  //walking leg1
  setPos(4, 135);
  delay(200);
  setPos(0, 40);
  delay(200);
  setPos(4, 84);
  setPos(8, 160);
  delay(200);
  setPos(0, 75);
  setPos(3, 60);
  setPos(1, 110);
  delay(200);
  //Preprep
  setPos(6, 140);
  delay(200);
  setPos(2, 105);
  delay(200);
  setPos(6, 85);
  setPos(10, 165);
}

int i = 0;
int n = 0;

void buff(){
  setPos(4, 55);
  setPos(5, 55);
  setPos(6, 55);
  setPos(7, 55);
  setPos(8, 120);
  setPos(9, 100);
  setPos(10, 120);
  setPos(11, 120);
}

void setup() {
  Serial.begin(9600);
  Ada.begin();
  Ada.setPWMFreq(60);
  stand_instanly();
  delay(4000);
  buff();
  delay(4000);
}

void loop() {
  while(i <= 50){
     i+=7;
     int r = round(static_cast<int>((static_cast<double>(i) / 180.0) * 5.95 * 180 / 17.514));


    Serial.println("I value :");
    Serial.print(i);
    Serial.println(" R value :");
    Serial.print(r);
    creepwalk_up(i,r);
  }
  while(n <= 20){
    creepwalk_down();
    n++;
  }


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
        case 16:
          stand_instanly();
          break;
          
        default:
          // Code to handle invalid or unrecognized values of the first integer
          setPos(serNum, degVal);
          break;

      }
    }
  }
}
