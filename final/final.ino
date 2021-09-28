#define TRIG1 30 //TRIG1 핀 설정 (초음파 보내는 핀)
#define ECHO1 31 //ECHO2 핀 설정 (초음파 받는 핀)
#define TRIG2 32
#define ECHO2 33
int min1 = 2;
int sec1 = 0; 
int sec2 = 0;
int button = 12;
int j = 0;

byte digits[10][7] =
{
  { 0, 0, 0, 0, 0, 0, 1 }, // 0
  { 1, 0, 0, 1, 1, 1, 1 }, // 1
  { 0, 0, 1, 0, 0, 1, 0 }, // 2
  { 0, 0, 0, 0, 1, 1, 0 }, // 3
  { 1, 0, 0, 1, 1, 0, 0 }, // 4
  { 0, 1, 0, 0, 1, 0, 0 }, // 5
  { 0, 1, 0, 0, 0, 0, 0 }, // 6
  { 0, 0, 0, 1, 1, 1, 1 }, // 7
  { 0, 0, 0, 0, 0, 0, 0 }, // 8
  { 0, 0, 0, 1, 1, 0, 0 }  // 9
};

byte failDigit[4][7] = {
  {0,1,1,1,0,0,0},
  {0,0,0,1,0,0,0},
  {1,1,1,1,0,0,1},
  {1,1,1,0,0,0,1}
};

byte colon[1][7] = {
  {1,0,1,1,0,1,1}
};

int piezo = 9;

const int LIMITVALUE = 300;

int cds1=A0;
int cds2=A1;
int cds3=A2;
int cds4=A3;
int cds5=A4;
int cds6=A5;
int cds7=A6;
int cds8=A7;

int val1, val2, val3, val4, val5, val6, val7, val8;

void setup() {
  for (int i = 0; i<7; i++) {
    pinMode(i+2, OUTPUT);
    pinMode(i+14, OUTPUT);
    pinMode(i+22, OUTPUT);
    pinMode(i+44, OUTPUT);
  }
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 14; i < 22; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 22; i < 29; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 44; i < 52; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(piezo, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  pinMode(TRIG1, OUTPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(button);
  //Serial.println(buttonState);
  // put your main code here, to run repeatedly:
  val2 = analogRead(cds2);
  val3 = analogRead(cds3);
  val4 = analogRead(cds4);
  val5 = analogRead(cds5);
  val6 = analogRead(cds6);
  val7 = analogRead(cds7);
  val8 = analogRead(cds8);


  long duration1, distance1;

  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);

  duration1 = pulseIn (ECHO1, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.

 //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  distance1 = duration1 * 17 / 1000; 

  long duration2, distance2;

  digitalWrite(TRIG2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);

  duration2 = pulseIn (ECHO2, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.

 //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  distance2 = duration2 * 17 / 1000; 


  if (min1 == 0 && sec1==0 && sec2==0) {
    // 피에조 울리면서 fail구문 띄우기
    for (int i = 0; i < 7; i++) {
    digitalWrite(2 + i, failDigit[0][i]);
    digitalWrite(14 + i, failDigit[1][i]);
    digitalWrite(22 + i, failDigit[2][i]);
    digitalWrite(44 + i, failDigit[3][i]);
    digitalWrite(piezo, 128);
    j = 1;
  }
  } else if(sec1==0 && sec2==0){ // 00초 일때
    for (int i = 0; i < 7; i++) {
    digitalWrite(14 + i, colon[0][i]);
    }
    min1--;
    displayDigitOne(min1);
    sec1=5;
    displayDigitThree(sec1);
    // val값을 최소값 알고리즘을 만들어서 최솟값만 비교하도록
    if ((distance1 != 0 && distance1 < 40) || distance2 != 0 && distance2 < 40){
      sec2=5;
      displayDigitFour(sec2);
      digitalWrite(piezo, 128);
    } else {
      sec2=9;
      displayDigitFour(sec2);
      digitalWrite(piezo, 0);
    }
  } else if (sec2==0) {
    sec1--;
    displayDigitThree(sec1);
    // val값을 최소값 알고리즘을 만들어서 최솟값만 비교하도록

    
    if (distance1 != 0 && distance1 < 40 || distance2 != 0 && distance2 < 40){
      sec2=5;
      displayDigitFour(sec2);
      digitalWrite(piezo, 128);
    } else {
      sec2=9;
      displayDigitFour(sec2);
      digitalWrite(piezo, 0);
    }
  } else {
    if (distance1 != 0 && distance1 < 40 || distance2 != 0 && distance2 < 40){
      digitalWrite(piezo, 128);
      if(sec2<5){
        if(sec1==0){
          if(min1==0){
            sec2=0;
            displayDigitFour(sec2);
          } else {
            if(sec2==5){
              sec2=0;
              displayDigitFour(sec2);
            } else {
              min1--;
              displayDigitOne(min1);
              sec1=5;
              displayDigitThree(sec1);
              sec2+=5;
              displayDigitFour(sec2);
            }
          }
        } else {
          sec1--;
          displayDigitThree(sec1);
          sec2+=5;
          displayDigitFour(sec2);
        }
      } else if(sec2==5) {
        if(sec1==0){
          if(min1==0){
            sec2=0;
            displayDigitFour(sec2);
          } else {
            sec2=0;
            displayDigitFour(sec2);
          }
        } else {
          sec2=0;
          displayDigitFour(sec2);
        }
      } else {
        sec2-=5;
        displayDigitFour(sec2);
      }
    } else {
      digitalWrite(piezo, 0);
      sec2--;
      displayDigitFour(sec2);
    }

  }
/*
// val값을 최소값 알고리즘을 만들어서 최솟값만 비교하도록
  if (distance1 != 0 && distance1 < 40 || distance2 != 0 && distance2 < 40){
    digitalWrite(piezo, 128);
  } else {
    digitalWrite(piezo, 0);
  }*/
  
  if (buttonState == 0 && j == 1) {
    min1 = 5;
    sec1 = 0;
    sec2 = 0;
    j = 0;
    digitalWrite(piezo, 0);
  }

  Serial.println("distance");
  Serial.println(distance1);
  Serial.println(distance2);
//  Serial.print(min1);
//  Serial.print(sec1);
//  Serial.println(sec2);
  delay(1000);
}

void displayDigitOne(int num) {
  int pin = 2;
  for (int i = 0; i < 7; i++) {
    digitalWrite(pin + i, digits[num][i]);
  }
}
void displayDigitTwo(int num) {
  int pin = 14;
  for (int i = 0; i < 7; i++) {
    digitalWrite(pin + i, digits[num][i]);
  }
}
void displayDigitThree(int num) {
  int pin = 22;
  for (int i = 0; i < 7; i++) {
    digitalWrite(pin + i, digits[num][i]);
  }
}
void displayDigitFour(int num) {
  int pin = 44;
  for (int i = 0; i < 7; i++) {
    digitalWrite(pin + i, digits[num][i]);
  }
}
