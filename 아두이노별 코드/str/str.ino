#include <Servo.h>

Servo myServo;

int servoPin = 13;
int button = 12;
int i = 0;
int j = 0;
int vibration_sensor=7;
int vib_data;
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 7
#define vib 2


void setup() {
  myServo.write(0);
  delay(2000);
  myServo.attach(servoPin);
  pinMode(vibration_sensor, INPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600); //시리얼통신 설정 9600
  Serial.println("----------------------vibration demo------------------------");
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
}

void loop() {
  int buttonState = digitalRead(button);
  vib_data=digitalRead(vibration_sensor);
  long measurement =TP_init();
  if(measurement > 5000&& i == 0){
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

long TP_init(){
  long measurement=pulseIn (vib, HIGH);
  return measurement;
}
