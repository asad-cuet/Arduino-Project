/*
   This car will go forward until no obstacle found in 25 cm distance. If any obstacle found at forward, it will stop,
   then turn the ultrasonic sensor at left and right. Measure the distance of obstacle at left and right side. If left distance is low,
   it will turn to left. If right distance ir low, it will turn to right. Now if forward is clear in 25cm, it will go forward.
   If not clear, again turn the ultrasonic sensor again and so on.
*/


#include<Servo.h>
Servo survo;

int t=300;
int ahead=100;
int left=250;
int right=0;

int trig = 13;    // sonar sensor
int echo = 12;
float distance;
float duration;

int MotorA_in1 =2;   //motor driver pin     motor A right side
int MotorA_in2 =3;
int MotorB_in3 =4;     // motor B left side         
int MotorB_in4 =5;
int MotorA_PWM =9;
int MotorB_PWM =10;

int spd= 255;
void setup() {
  survo.attach(6);
  Serial.begin(9600);
       pinMode(trig, OUTPUT);  //ultrasonic sensor
       pinMode(echo, INPUT);
   
  pinMode(MotorA_in1, OUTPUT);
  pinMode(MotorA_in2, OUTPUT);
  pinMode(MotorB_in3, OUTPUT);
  pinMode(MotorB_in4, OUTPUT);
  pinMode(MotorA_PWM, OUTPUT);
  pinMode(MotorB_PWM, OUTPUT);  
}
void loop() {

        // default things
        analogWrite(MotorA_PWM, spd);   //used PWM
        analogWrite(MotorB_PWM, spd);
        survo.write(ahead);
        
        start:
        distance=sonar();

        if(distance>25)
        {
          RobotForward();
        }

        if(distance<25 && distance!=0) 
        {
          RobotStop();
          Survo();
          goto start;
        }

}
        
 
 
           
// robot movement function  
 
void RobotForward() {

  digitalWrite(MotorA_in1, LOW);  //clockwiwse
  digitalWrite(MotorA_in2, HIGH);
  digitalWrite(MotorB_in3, HIGH);
  digitalWrite(MotorB_in4, LOW);

}

void RobotStop() {

  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);

}

void RobotBackward() {

  digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
  
}


void RobotRight() {
  
  digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, HIGH);
  digitalWrite(MotorB_in4, LOW);

}

void RobotLeft() {

  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, HIGH);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);   
}

void sonar() {
        digitalWrite(trig, LOW);
        delay(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig,LOW);
        duration =pulseIn(echo, HIGH); 
        return (duration*0.0332)/2;  //distance, calculated in cm

     //   Serial.print("distance is=");
     //   Serial.print(distance);
     //   Serial.print("cm\n");
}


void Survo() {
  survo.write(left);
  delay(t);
  distance_1=sonar();  
  delay(t);

  survo.write(right);
  delay(t);
  distance_2=sonar();
  delay(t);

  survo.write(ahead);
  delay(500);

  if(distance_1>distance_2) {
          RobotLeft();
          delay(500);
        }
        else {
          RobotRight();
          delay(500);
        }
        
}
