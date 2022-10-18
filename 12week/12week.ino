int pinA = D12; //segment 각각의 pin 디지털 핀으로 선언
int pinB = D11;
int pinC = D10;
int pinD = 15;
int pinE = 14;
int pinF = D7;
int pinG = D6;

int PORT1 = D5; // 각 seg를 디지털 핀으로 선언
int PORT2 = D4;
int PORT3 = D3;
int PORT4 = D8;


const byte interruptPin1 = D2;
const byte interruptPin2 = D9;

volatile int count = 0;
volatile int Flag = 0;

//사용 편의를 위해 각 seg의 pin을 배열로 선언
int find_pin[7] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG};

//사용 편의를 위해 각 자리 seg를 배열로 선언
int find_port[4] = {PORT1, PORT2, PORT3, PORT4};

//0~9까지 숫자를 dp미선언과 dp선언으로 2차원배열 선언
int seg_data[10][7] = {
  {1,1,1,1,1,1,0},{0,1,1,0,0,0,0},{1,1,0,1,1,0,1},{1,1,1,1,0,0,1},{0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},{1,0,1,1,1,1,1},{1,1,1,0,0,1,0},{1,1,1,1,1,1,1},{1,1,1,1,0,1,1}
};

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

  pinMode(interruptPin1, INPUT);
  pinMode(interruptPin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin1),upnum,FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2),downnum,FALLING);
}

void loop() {
  int d1 = count/1000; // 1000의 자리수 표현
  int d2 = count %1000 /100; // 100의 자리수 표현
  int d3 = count%100/10; // 10의 자리수 표현
  int d4 = count %10; // 1의 자리수 표현

  print_all(1,d1); // 1번째 segment display
  delay(2);
  print_all(2,d2); // 2번째 segment display
  delay(2);
  print_all(3,d3); // 3번째 segment display
  delay(2);
  print_all(4,d4); // 4번째 segment display
  delay(2);
  
  if (Serial.available()) //Serial buffer에 들어온 데이터를 점검하는 구간
  {
    char chr = Serial.read(); //Serial 통신 읽어들이는 구간
    
    if (chr==0x55 || chr==0x75) 
    {
      count++;
    }
    else if (chr==0x44 || chr==0x64) 
    {
      count--;
    }
  }
  Serial.print(count);
  Serial.println(); //줄바꿈을 하여 문자들을 출력해줌
}

void print_all(int position, int number) { //각 자리에 원하는 숫자를 나타내주는 함수
  for(int i = 0; i < 4; i++){ //각 자리에 해당하는 seg만 display해주는 반복문
    if(i+1 == position){ //해당하는 자리의 seg만 LOW, 나머지는 HIGH
      digitalWrite(find_port[i], LOW);
    }else{
      digitalWrite(find_port[i], HIGH);
    }
  }

  for(int i = 0; i < 7; i++){ //원하는 숫자를 표시해주는 반복문
      if(seg_data[number][i] == 1){ //1로 표시된 seg만 HIGH, 나머지는 LOW로 표시
        digitalWrite(find_pin[i], HIGH);
      }else{
        digitalWrite(find_pin[i], LOW);
      }
   }
}

void upnum(){
  count++;
}

void downnum(){
  count--;
}
