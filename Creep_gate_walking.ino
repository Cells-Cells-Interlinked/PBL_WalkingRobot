#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
//#include <Servo.h>

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
    setPos(11, 150);
    delay(500);
    Serial.println("Stand up: complete");
}

void linear(){
    setPos(0, 45);
    setPos(2, 65);
    setPos(1, 115);
    setPos(3, 100);
    delay(500);
}

void step1(){
//prepleg1
    setPos(3, 100);
    setPos(1, 60);
    delay(700);
    setPos(4, 120);
    setPos(8, 120);
    delay(700);
    setPos(0, 50);
    delay(500);
    setPos(4, 60);
    delay(700);
//thrust1
    setPos(1, 110);
    setPos(3, 60);
    setPos(10, 145);
    setPos(8, 155);
    delay(1000);

// //regain pos1
//     setPos(2, 105);
//     setPos(10, 160);
//     delay(700);
//     setPos(6, 50);
//     setPos(10, 140);
//     delay(1000);

//     setPos(1, 92);
//     setPos(9, 125);
//     delay(700);
//     setPos(5, 70);
//     delay(1000);

// //prepleg2
//     setPos(7,95);
//     delay(700);
//     setPos(11,110);
//     delay(700);
//     setPos(3,100);
//     delay(700);
//     setPos(7, 60);
//     delay(700);
// //thrust2
//     setPos(11,140);
//     setPos(9, 105);
//     setPos(0, 90);
//     setPos(2,55);
//     delay(1000);

// regain pos 2
    stand_instanly();
    
}
void step2(){
  //prepleg1
    setPos(0, 50);
    setPos(2, 105);
    delay(700);
    setPos(7, 120);
    setPos(11, 120);
    delay(700);
    setPos(3, 100);
    delay(500);
    setPos(7, 50);
    delay(700);
//thrust1
    setPos(0, 90);
    setPos(2, 55);
    setPos(11, 145);
    setPos(9, 125);
    delay(1000);

// //regain pos1
//     setPos(2, 105);
//     setPos(10, 160);
//     delay(700);
//     setPos(6, 50);
//     setPos(10, 140);
//     delay(1000);

//     setPos(1, 92);
//     setPos(9, 125);
//     delay(700);
//     setPos(5, 75);
//     delay(1000);

// //prepleg2
//     setPos(7,95);
//     delay(700);
//     setPos(11,120);
//     delay(700);
//     setPos(3,100);
//     delay(700);
//     setPos(7, 70);
//     delay(700);
// //thrust2
//     setPos(11,140);
//     setPos(9, 105);
//     setPos(0, 90);
//     setPos(2,55);
//     delay(1000);
//regain2
    stand_instanly();
}
void step3(){
//prepleg1
    setPos(3, 100);
    setPos(1, 60);
    delay(700);
    setPos(4, 120);
    setPos(8, 100);
    delay(700);
    setPos(0, 50);
    delay(500);
    setPos(4, 60);
    delay(700);
//thrust1
    setPos(1, 110);
    setPos(3, 60);
    setPos(10, 145);
    setPos(8, 155);
    delay(1000);
//regain3
    // stand_instantly();
}
void step4(){
  //prepleg1
    setPos(0, 50);
    setPos(2, 105);
    delay(700);
    setPos(7, 120);
    setPos(11, 120);
    delay(700);
    setPos(3, 100);
    delay(500);
    setPos(7, 50);
    delay(700);
//thrust1
    setPos(0, 90);
    setPos(2, 55);
    setPos(11, 145);
    setPos(9, 125);
    delay(1000);
}

//End of Functions

void setup() {
  Serial.begin(9600);
  Ada.begin();
  Ada.setPWMFreq(60);
  stand_instanly();
  //compensate();
  delay(5000);
}
void walking(){
  step1();
  delay(700);
  step2();
  delay(700);
  // step3();
  // delay(700);
  // step4();
}
// void compensate(){
//   setPos(11, 145);
//   setPos(10, 155);
// }
void creepwalk(){
  //prep
  setPos(2, 105);
  setPos(3, 60);
  delay(500);
  //walking leg 4
  setPos(7,140);
  delay(500);
  setPos(3,100);
  delay(500);
  setPos(7, 85);
  delay(500);
  setPos(3, 80);
  setPos(0, 90);
  setPos(1, 110);
  setPos(2, 55);
  delay(500);
  //walking leg2
  setPos(5, 130);
  delay(500);
  setPos(1 ,60);
  delay(500);
  setPos(5, 90);
  delay(500);
  //walking leg1
  setPos(4, 135);
  delay(500);
  setPos(0, 40);
  delay(500);
  setPos(4, 84);
  delay(500);
  setPos(0, 75);
  setPos(3, 60);
  setPos(1, 110);
  delay(500);
  //Preprep
  setPos(6, 140);
  delay(500);
  setPos(2, 105);
  delay(500);
  setPos(6, 85);
}

void loop() {
  creepwalk();

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
          step1();
          break;

        case 15:
          step2();
          break;
        
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

      }
    }
  }
}
