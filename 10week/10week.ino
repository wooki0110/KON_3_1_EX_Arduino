#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"

#define HW_TIMER_INTERVAL_MS 1

//Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer(NRF_TIMER_3);

NRF52_MBED_ISRTimer ISR_Timer;

const byte ledRed = 9;
const byte ledGreen = 10;
const byte ledBlue = 11;
const byte interruptPin = 8;
volatile byte stateR = LOW;
volatile byte stateG = LOW;
volatile byte stateB = LOW;
volatile byte state2 = HIGH;

#define TIMER_INTERVAL_1S 50L
#define TIMER_INTERVAL_2S 500L
#define TIMER_INTERVAL_3S 5000L

void TimerHandler()
{
  ISR_Timer.run();
}

void blinkled1()
{
  if(state2 == HIGH){
    stateR = !stateR;
    digitalWrite(ledRed, stateR);
  }
  else{
  digitalWrite(ledRed, LOW);
  }
}

void blinkled2()
{
  if(state2 == HIGH){
    stateG = !stateG;
    digitalWrite(ledGreen, stateG);
  }
  else{
  digitalWrite(ledGreen, LOW);
  }
}

void blinkled3()
{
  if(state2 == HIGH){
    stateB = !stateB;
    digitalWrite(ledBlue, stateB);
  }
  else{
  digitalWrite(ledBlue, LOW);
  }
}

void ledstop()
{
  state2 = !state2;
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(interruptPin),ledstop,RISING);
  pinMode(interruptPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, blinkled1);
  ISR_Timer.setInterval(TIMER_INTERVAL_2S, blinkled2);
  ISR_Timer.setInterval(TIMER_INTERVAL_3S, blinkled3);
}

void loop() {
  // nothing
}
