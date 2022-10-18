int pinA = D12;
int pinB = D11;
int pinC = D10;
int pinD = D9;
int pinE = D8;
int pinF = D7;
int pinG = D6;
int pinDP  = D13;

int PORT1 = D5;
int PORT2 = D4;
int PORT3 = D3;
int PORT4 = D2;

int find_pin[8] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};
int find_port[4] = {PORT1, PORT2, PORT3, PORT4};
int seg_data[10][8] = {
  {1,1,1,1,1,1,0,0},{0,1,1,0,0,0,0,0},{1,1,0,1,1,0,1,0},{1,1,1,1,0,0,1,0},{0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},{1,0,1,1,1,1,1,0},{1,1,1,0,0,1,0,0},{1,1,1,1,1,1,1,0},{1,1,1,1,0,1,1,0}
};
int seg_data_dp[10][8] = {
  {1,1,1,1,1,1,0,1},{0,1,1,0,0,0,0,1},{1,1,0,1,1,0,1,1},{1,1,1,1,0,0,1,1},{0,1,1,0,0,1,1,1},
  {1,0,1,1,0,1,1,1},{1,0,1,1,1,1,1,1},{1,1,1,0,0,1,0,1},{1,1,1,1,1,1,1,1},{1,1,1,1,0,1,1,1}
};

const int delay_time = 5;

void setup() {

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinDP, OUTPUT);
  
  pinMode(PORT1, OUTPUT);
  pinMode(PORT2, OUTPUT);
  pinMode(PORT3, OUTPUT);
  pinMode(PORT4, OUTPUT);
}

void loop() {
  static int count = 9000;
  if(count == 10000){
    count = 0;
  }else{
    count++;
  }

  int d1 = count/1000;
  int d2 = count %1000 /100;
  int d3 = count%100/10;
  int d4 = count %10;

  print_all(1,d1);
  delay(2);
  print_dp(2,0);
  delay(2);
  print_all(2,d2);
  delay(2);
  print_all(3,d3);
  delay(2);
  print_all(4,d4);
  delay(2);

}

void print_all(int position, int number) {
  for(int i = 0; i < 4; i++){
    if(i+1 == position){
      digitalWrite(find_port[i], LOW);
    }else{
      digitalWrite(find_port[i], HIGH);
    }
  }

  for(int i = 0; i < 8; i++){
    if(position != 2){
      if(seg_data[number][i] == 1){
        digitalWrite(find_pin[i], HIGH);
      }else{
        digitalWrite(find_pin[i], LOW);
      }
    }
    else{
     if(seg_data[number][i] == 1){
        digitalWrite(find_pin[i], HIGH);
      }else{
        digitalWrite(find_pin[i], LOW);
      }
    }
  }
}

void print_dp(int position, int number) {
  for(int i = 0; i < 4; i++){
    if(i+1 == position){
      digitalWrite(find_port[i], LOW);
    }else{
      digitalWrite(find_port[i], HIGH);
    }
  }

  for(int i = 0; i < 7; i++){
    if(position != 2){
      if(seg_data[number][i] == 1){
        digitalWrite(find_pin[i], HIGH);
      }else{
        digitalWrite(find_pin[i], LOW);
      }
    }
    else{
     digitalWrite(find_pin[i], LOW);
     digitalWrite(pinDP, HIGH);
    }
  }
}
