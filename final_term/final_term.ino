int pinA = D12; //segment 각각의 pin 디지털 핀으로 선언
int pinB = D11;
int pinC = D10; //A2 pin
int pinD = D9; //A1 pin
int pinE = 14; //A0 pin
int pinF = D7;
int pinG = D6;

int PORT1 = D2; // 각 seg를 디지털 핀으로 선언
int PORT2 = D3;
int PORT3 = D4;
int PORT4 = D5;

int stoppin1 = D8;

volatile int count = 0;

int find_pin[8] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG};
int find_port[4] = {PORT1, PORT2, PORT3, PORT4};
int seg_data_dp[12][7]=
{
  {0,0,1,0,0,0,0}, 
  {0,1,1,0,0,0,0}, 
  {1,1,1,0,0,0,0}, 
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0}, 
  {1,0,0,0,0,1,0}, 
  {1,0,0,0,1,1,0}, 
  {1,0,0,1,1,1,0}, 
  {1,0,0,1,0,0,0},
  {1,0,0,1,0,0,0}, 
  {1,1,1,1,0,0,0}, 
};


#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"

#define HW_TIMER_INTERVAL_MS 1

//Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

NRF52_MBED_ISRTimer ISR_Timer;

#define TIMER_INTERVAL_1S 500L

void TimerHandler()
{
  ISR_Timer.run();
}

void seq()
{
  if(count > 12){
    count = 0;
  }
  count++;
}

void setup() {
  Serial.begin(9600);
  pinMode(pinA, OUTPUT); //segA~Dp까지의 디지털핀을 출력으로 선언
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  
  pinMode(PORT1, OUTPUT); //각 seg를 나타내는 디지털 핀을 출력으로 선언
  pinMode(PORT2, OUTPUT);
  pinMode(PORT3, OUTPUT);
  pinMode(PORT4, OUTPUT);

  pinMode(stoppin1, INPUT_PULLUP);
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, seq);
}

void loop() {
    if(count == 1){
    print_all(1,count-1);
    delay(1);
  }
  else if(count < 4){
    print_all(1,count-1);
    delay(1);
  }
  else if(count == 4) {
    print_all(1,2);
    delay(1);
    print_all(2,count-1);
    delay(1);
  }
  else if(count == 5) {
    print_all(1,2);
    delay(1);
    print_all(2,3);
    delay(1);
    print_all(3,count-1);
    delay(1);
  }
  else if(count < 10) {
    print_all(1,2);
    delay(1);
    print_all(2,3);
    delay(1);
    print_all(3,4);
    delay(1);
    print_all(4,count-1);
    delay(1);
  }
  else if(count == 10){
    print_all(1,2);
    delay(1);
    print_all(2,3);
    delay(1);
    print_all(3,count-1);
    delay(1);
    print_all(4,8);
    delay(1);
  }
  else if(count == 11) {
    print_all(1,2);
    delay(1);
    print_all(2,count-1);
    delay(1);
    print_all(3,9);
    delay(1);
    print_all(4,8);
    delay(1);
  }
  else{
    print_all(1,count-1);
    delay(1);
    print_all(2,10);
    delay(1);
    print_all(3,9);
    delay(1);
    print_all(4,8);
    delay(1);
    print_off();
  }
}

void print_all(int position, int number) {
  for(int i = 0; i < 4; i++){
    if(i+1 == position){
      digitalWrite(find_port[i], LOW);
    }else{
      digitalWrite(find_port[i], HIGH);
    }
  }

  for(int i = 0; i < 7; i++){
    if(seg_data_dp[number][i] == 1){
        digitalWrite(find_pin[i], HIGH);
      }else{
        digitalWrite(find_pin[i], LOW);
      }
  }
}

void print_off() {
  for(int i = 0; i < 4; i++){
    digitalWrite(find_port[i], HIGH);
  }
}
