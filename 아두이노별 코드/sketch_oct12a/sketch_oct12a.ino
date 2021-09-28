
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
void setup() {
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
}
void loop() {
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    delay(1000);
  }
}
void displayDigit(int num) {
  int pin = 2;
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
