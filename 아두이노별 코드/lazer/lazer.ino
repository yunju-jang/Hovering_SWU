int min1 = 5;
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

  Serial.println(val2);
  Serial.println(val3);
  Serial.println(val4);
  Serial.println(val5);
  Serial.println(val6);
  Serial.println(val7);
  Serial.println(val8);


    if (min1 == 0 && sec1==0 && sec2==0) {
    // 피에조 울리면서 fail구문 띄우기
    for (int i = 0; i < 7; i++) {
    digitalWrite(2 + i, failDigit[0][i]);
    digitalWrite(14 + i, failDigit[1][i]);
    digitalWrite(22 + i, failDigit[2][i]);
    digitalWrite(44 + i, failDigit[3][i]);
    analogWrite(piezo, 128);
    delay(5000);
    analogWrite(piezo, 0);
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
    if (val2 < LIMITVALUE || val3 < LIMITVALUE || val4 < LIMITVALUE || 
    val5 < LIMITVALUE || val6 < LIMITVALUE || val7 < LIMITVALUE || val8 < LIMITVALUE){
      sec2=5;
      displayDigitFour(sec2);
      analogWrite(piezo, 128);
    } else {
      sec2=9;
      displayDigitFour(sec2);
      analogWrite(piezo, 0);
    }
  } else if (sec2==0) {
    sec1--;
    displayDigitThree(sec1);
    // val값을 최소값 알고리즘을 만들어서 최솟값만 비교하도록
    if (val2 < LIMITVALUE || val3 < LIMITVALUE || val4 < LIMITVALUE || 
    val5 < LIMITVALUE || val6 < LIMITVALUE || val7 < LIMITVALUE || val8 < LIMITVALUE){
      ec2=5;
      displayDigitFour(sec2);
      analogWrite(piezo, 128);
    } else {
      sec2=9;
      displayDigitFour(sec2);
      analogWrite(piezo, 0);
    }
  } else {
    // val값을 최소값 알고리즘을 만들어서 최솟값만 비교하도록
    if (val2 < LIMITVALUE || val3 < LIMITVALUE || val4 < LIMITVALUE || 
    val5 < LIMITVALUE || val6 < LIMITVALUE || val7 < LIMITVALUE || val8 < LIMITVALUE){
      analogWrite(piezo, 128);
      if(sec2<=5){
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
      } else {
        sec2-=5;
        displayDigitFour(sec2);
      }
    } else {
      analogWrite(piezo, 0);
      sec2--;
      displayDigitFour(sec2);
    }

  }

// val값을 최소값 알고리즘을 만들어서 최솟값만 비교하도록
  if (val2 < LIMITVALUE || val3 < LIMITVALUE || val4 < LIMITVALUE || 
  val5 < LIMITVALUE || val6 < LIMITVALUE || val7 < LIMITVALUE || val8 < LIMITVALUE){
    analogWrite(piezo, 128);
  } else {
    analogWrite(piezo, 0);
  }
  
  if (buttonState == 0 && j == 1) {
    min1 = 5;
    sec1 = 0;
    sec2 = 0;
    j = 0;
    analogWrite(piezo, 0);
  }

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
