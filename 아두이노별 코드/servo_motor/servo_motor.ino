#include <Servo.h>

Servo myServo;

int servoPin = 8;
int sensor = A0;
int button = 13;
int i = 0;

void setup() {
  myServo.write(0);
  delay(2000);
  myServo.attach(servoPin);
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(button);
  int pres = map(analogRead(A0),0,1023,0,255);
  Serial.println(pres);
  if (pres>69 && i == 0) {
    myServo.write(0);
    delay(2000);
    myServo.write(90);
    delay(2000);
    i = 1;
  }
  if (buttonState == 0 && i == 1) {
    myServo.write(90);
    delay(2000);
    myServo.write(0);
    delay(2000);
    i = 0;
  }
}


/*
#include <Servo.h>                        //서보모터 라이브러리 호출

int sensor = A0;      r                     //압전 센서핀을 11번으로 설정

Servo servo;                            //서보모터 제어문
int servoPin = 11;                            //서보모터핀을 A2번으로 설정

int angle = 0;

void setup(){
  Serial.begin(9600);                      //시리얼 통신, 속도는 9600
  
  servo.attach(servoPin);                    //모터 시작 
}

void loop(){
  int pur = analogRead(sensor);             //압전 센서의 데이터 받아오기
  if (pur > 300) {
    for(angle = 0; angle < 90; angle++) 
      { 
        servo.write(angle); 
        delay(15); 
      } 
  }
  Serial.println(sensor);
  //Serial.println(angle);                   //모터값을 시리얼 모니터로 출력
}
*/
