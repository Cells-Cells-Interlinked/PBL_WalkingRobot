/* credits to VDEngineering video for the kalman filter algorithm
 *  youtube video: https://www.youtube.com/watch?v=ruB917YmtgE
 */

// ULTRASONIC //
// Pins

//Ultrasonic1
#define echo_1 8
#define trig_1 9
//ultrasonic2
#define echo_2 3
#define trig_2 2

// Constrains
const int maxdist = 335;
const float mindist = 2.5;

int distance_1, duration_1, distance_2, duration_2;

//int kaldist;

void setup(){
  pinMode(trig_1, OUTPUT);
  pinMode(echo_1, INPUT);
  pinMode(trig_2, OUTPUT);
  pinMode(echo_2, INPUT);
  Serial.begin(9600);
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

      return distance_1;
      break;
    case 2:
      duration_2 = pulseIn(echo_2, HIGH);
      distance_2 = (duration_2*0.034)/2;

      Serial.print("Distance_2 :");
      Serial.print(distance_2);
      Serial.print("\n");

      return distance_2;
      break;

  }
}

void loop(){

  usonic_transmit(1);
  readUltrasonic(1);
  
  usonic_transmit(2);
  readUltrasonic(2);


  delay(300);
}
