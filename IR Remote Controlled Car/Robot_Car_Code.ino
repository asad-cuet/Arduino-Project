#include <IRremote.h>
#include<Servo.h>
Servo survo;
int i,x;
int RECV_PIN = 13;   //ir recever sensor code
IRrecv irrecv(RECV_PIN);
decode_results results;

int trig = 11;
int echo = 12;
float distance,duration;

int MotorA_in1 =2;   //motor driver pin
int MotorA_in2 =3;
int MotorB_in3 =4;
int MotorB_in4 =5;
int MotorA_PWM =9;
int MotorB_PWM =10;
char sms;
int spd= 150;
void setup() {
  survo.attach(6);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
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
        analogWrite(MotorA_PWM, spd);   //used PWM
        analogWrite(MotorB_PWM, spd);
        survo.write(0);
  
        //ultrasonic sensor
        digitalWrite(trig, HIGH);
        delay(0.01);
        digitalWrite(trig, LOW);
        duration =pulseIn(echo, HIGH); 
        distance=duration*0.0332/2;  // calculated in cm

                       // Robot self protect
         
        if(distance<5) {
        RobotStop();
        survo.write(90); //turn left
        delay(200);
        survo.write(0);
        delay(100);
        survo.write(-90); //turn right 
        delay(200);
        survo.write(0);
        RobotBackward();
        delay(300);     
              }

  
        //IF you use IR remote
      if (irrecv.decode(&results)) {  
                irrecv.resume(); // Receive the next value
  
          if(results.value == 0xF) {   // F=forward code
            RobotForward();
          }
          if(results.value == 0x678) {  //678 is not code,just example
        RobotBackward(); 
          }
          if(results.value == 0x576) {
           RobotRight();
          }
          if(results.value == 0x76) {
            RobotLeft();
              }
      }


 

                        // iF you use Andriod Phone
   
   if(Serial.available()) {
   sms = Serial.read();
   }
   if(sms == 'S') {
    RobotStop();
   }
   if(sms == 'F') {
    RobotForward();
   }
   if(sms == 'R') {
    RobotRight();
   }
   if(sms == 'L') {
    RobotLeft();
   }

                      // Speed control
   if(sms == '0') {
    spd = 0;
   }
      if(sms == '1') {
    spd = 28;
   }
      if(sms == '2') {
    spd = 56;
   }
      if(sms == '3') {
    spd = 84;
   }
      if(sms == '4') {
    spd = 112;
   }
      if(sms == '5') {
    spd = 140;
   }
      if(sms == '6') {
    spd = 168;
   }
      if(sms == '7') {
    spd = 196;
   }
      if(sms == '8') {
    spd = 224;
   }
      if(sms == '9') {
    spd = 255;
   }

                 // Robot control by itself
   if(sms == 'run') {
    start:
      RobotGo();
  if(distance<5) {
    RobotBackward();
    delay(150);
    survo.write(0);
    survo.write(90);  //turn left
    delay(100);
    survo.write(0);
    delay(100);
    survo.write(-90);  //turn right
    delay(100);
    survo.write(0);
    RobotRight();
    delay(100);
    
                 }
    if(sms == 'off') {
      goto end;
    }
    goto start;
    end:
    return 0;
}              
   
   

}
   
   



// robot movement function   
void RobotForward() {
  survo.write(0);
  digitalWrite(MotorA_in1, HIGH);   //clockwise
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);     //anti clockwise
  digitalWrite(MotorB_in4, HIGH);

}

void RobotStop() {
  survo.write(0);
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);
}

void RobotBackward() {
  survo.write(270);
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, HIGH);
  digitalWrite(MotorB_in3, HIGH);
  digitalWrite(MotorB_in4, LOW);
}


void RobotRight() {
  survo.write(-90);  
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
}

void RobotLeft() {
  survo.write(90);
  digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);
}

void RobotGo() {
  for(i=0;i<=90;i=i+5) {
    survo.write(i);
    delay(90);
    if(i == '90') {
      for(x=90;x>=0;x=x-5) {
        survo.write(x);
        delay(90);
      }
    }
  }
  digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
}
