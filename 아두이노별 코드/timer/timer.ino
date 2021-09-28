int min1 = 1;
int sec1 = 0; 
int sec2 = 0;

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
}
void loop() {
  if (min1 == 0 && sec1==0 && sec2==0) {
  // 피에조 울리면서 fail구문 띄우기
    for (int i = 0; i < 7; i++) {
    digitalWrite(2 + i, failDigit[0][i]);
    digitalWrite(14 + i, failDigit[1][i]);
    digitalWrite(22 + i, failDigit[2][i]);
    digitalWrite(44 + i, failDigit[3][i]);
  }
  } else if(sec1==0 && sec2==0){ // 00초 일때
    for (int i = 0; i < 7; i++) {
    digitalWrite(14 + i, colon[0][i]);
  }
    min1--;
    displayDigitOne(min1);
    sec1=5;
    displayDigitThree(sec1);
    sec2=9;
    displayDigitFour(sec2);
  } else if (sec2==0) {
    sec1--;
    displayDigitThree(sec1);
    sec2=9;
    displayDigitFour(sec2);
  } else {
    sec2--;
    displayDigitFour(sec2);
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

/*
int seg[] = {2,3,4,5,6,7,8,9};
byte digits[10][8] = {
  {1,1,0,0,0,0,0,0},
  {1,1,1,1,1,0,0,1},
  {1,0,1,0,0,1,0,0},
  {1,0,1,1,0,0,0,0},
  {1,0,0,1,1,0,0,1},
  {1,0,0,1,0,0,1,0},
  {1,0,0,0,0,0,1,0},
  {1,1,1,1,1,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0}
  };
void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<8; i++) {
    pinMode(seg[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<10; i++) {
    for (int j=0; j<8; j++) {
      digitalWrite(seg[j], digits[i][j]);
    }
    delay(1000);
  }
}*/
