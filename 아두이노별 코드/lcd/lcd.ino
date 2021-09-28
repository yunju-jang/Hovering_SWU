#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 0x3F I2C 주소를 가지고 있는 16x2 LCD객체를 생성합니다.(I2C 주소는 LCD에 맞게 수정해야 합니다.)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LIMITVALUE = 700;
//센서별 핀번호 선언
int lasor = 8;
int piezo = 9;          
int cds = A0;

int min = 0;
int sec1 = 1;
int sec2 = 0;

//조도센서의 값을 저장하는 변수 선언
int val;

void setup() {   

              
  //핀모드 설정 
  pinMode(piezo, OUTPUT); 
  pinMode(cds, INPUT);
  pinMode(lasor, OUTPUT);
  Serial.begin(9600); //시리얼 통신 초기화

  // I2C LCD를 초기화 합니다..
  lcd.init();
  // I2C LCD의 백라이트를 켜줍니다.
  lcd.backlight();

  
}

void loop() {

//lcd

  lcd.setCursor(0,0);
  lcd.print(min);
  lcd.setCursor(1,0);
  lcd.print(":");
  lcd.setCursor(2,0);
  lcd.print(sec1);
  lcd.setCursor(3,0);
  lcd.print(sec2);

  if (min == 0 && sec2 == 0 && sec1 == 0) { 
    //타임오버, 피에조 소리
    lcd.setCursor(0,0);
    lcd.print("FAIL : TIMEOVER");
  } else if (sec1 == 0 && sec2 == 0) {
    //초가 00일때
    min--;
    sec1 = 5;
    sec2 = 9;
    delay(1000);
  } else if (sec2 == 0){
    sec1--;
    sec2 = 9;
    delay(1000);
  } else {
    sec2--;
    delay(1000);
  }

  
  
//  int value = random(0, 3);
//  // 랜덤 값이 0이라면 아래의 조건을 실행합니다.
//  if (value == 0) {
//    // 0번째 줄 0번째 셀부터 입력하게 합니다.
//    lcd.setCursor(0,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
//    lcd.print("Maze Droner");       // 문구를 출력합니다.
//  }
//  // 랜덤 값이 1이라면 아래의 조건을 실행합니다.
//  else if (value == 1) {
//    lcd.setCursor(0,1);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
//    lcd.print("  Hello World!!  ");     // 문구를 출력합니다.
//  }
//  // 랜덤 값이 2이라면 아래의 조건을 실행합니다.
//  else if (value == 2) {
//    // 0번째 줄 0번째 셀부터 입력하게 합니다.
//    lcd.setCursor(0,0);
//    // 아래의 문장을 출력합니다.
//    lcd.print("Maze Droner");
//    // 1번째 줄 0번째 셀부터 입력하게 합니다.
//    lcd.setCursor(0,1);
//    // 아래의 문장을 출력합니다.
//    lcd.print("  Hello World!!  ");
//  }
//  // 1초간 대기합니다.
//  delay(1000);
//  // LCD의 모든 내용을 삭제합니다.
//  lcd.clear();


 //레이져모듈
  digitalWrite(lasor, HIGH); //레이저모듈핀에 항상 HIGH값을 입력
  val = analogRead(cds); //조도센서로 부터 값을 읽어들인다
  Serial.println(val); //시리얼 모니터에 출력
  if(val < LIMITVALUE) { //값이 일정값 이하로 떨어질 경우
    analogWrite(piezo, 128);//피에조부저에서 소리가 난다
    //타이머 5초 깎기
    if (sec1 == 0 && sec2 < 5) {
      int r = 4 - sec2;
      if (r == 0) {
        sec2 = 0;
        Serial.println("a");
      } else {
        min--;
        sec1 = 5;
        sec2 = 10 - r;
        Serial.println("b");
      }
    } else if (sec2 < 5){
      Serial.println("c");
      int r = 4 - sec2;
      if (r == 0) {
        Serial.println("d");
        sec2 = 0;
      } else {
      sec1--;
      sec2 = 10 - r;
      Serial.println("e");
      }
    } else {
      sec2 -= 4;
      Serial.println("f");
    }
  }
  else { //그 이외의 경우
    analogWrite(piezo, 0); //소리가 울리지 않는다 
  } 
 
  delay(100);                       // 1초 대기
}
