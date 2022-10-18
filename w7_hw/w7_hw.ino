int LEDS[4] = {10,11,12,13};
int COLS[4] = {6,7,8,9};
int ROWS[4] = {2,3,4,5};

void setup() {
  //Make column pins output
  //Make row pins input
  for (int i = 0; i < 4; i++) {
    pinMode(ROWS[i], INPUT_PULLUP);
    pinMode(COLS[i], OUTPUT);
    digitalWrite(COLS[i], HIGH);
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], LOW);
  }
}

void loop() {
  // col[0]
  digitalWrite(COLS[0], LOW);
  if(digitalRead(COLS[0]) == LOW){
    if(digitalRead(ROWS[0]) == LOW && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == LOW && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], HIGH);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == LOW && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == LOW){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], HIGH);
    }else{;}
  }
  
  for (int i = 0; i < 4; i++){
    digitalWrite(COLS[i], HIGH);
  }
  
 //col[1]
  digitalWrite(COLS[1], LOW);
  if(digitalRead(COLS[1]) == LOW){
    if(digitalRead(ROWS[0]) == LOW && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == LOW && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], HIGH);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == LOW && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == LOW){
      digitalWrite(LEDS[0], LOW);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], HIGH);
    }else{;}
  }
  for (int i = 0; i < 4; i++){
    digitalWrite(COLS[i], HIGH);
  }
  
  //COL[2]
  digitalWrite(COLS[2], LOW);
  if(digitalRead(COLS[2]) == LOW){
    if(digitalRead(ROWS[0]) == LOW && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == LOW && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], HIGH);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == LOW && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == LOW){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], LOW);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], HIGH);
    }else{;}
  }
  
  for (int i = 0; i < 4; i++){
    digitalWrite(COLS[i], HIGH);
  }
  
  //COL[3]
  digitalWrite(COLS[3], LOW);
  if(digitalRead(COLS[3]) == LOW){
    if(digitalRead(ROWS[0]) == LOW && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == LOW && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], LOW);
      digitalWrite(LEDS[3], HIGH);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == LOW && digitalRead(ROWS[3]) == HIGH){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], LOW);
    }else if(digitalRead(ROWS[0]) == HIGH && digitalRead(ROWS[1]) == HIGH && digitalRead(ROWS[2]) == HIGH && digitalRead(ROWS[3]) == LOW){
      digitalWrite(LEDS[0], HIGH);
      digitalWrite(LEDS[1], HIGH);
      digitalWrite(LEDS[2], HIGH);
      digitalWrite(LEDS[3], HIGH);
    }else{;}
  }

  for (int i = 0; i < 4; i++){
    digitalWrite(COLS[i], HIGH);
  }

  delay(100);
  digitalWrite(LEDS[0], LOW);
  digitalWrite(LEDS[1], LOW);
  digitalWrite(LEDS[2], LOW);
  digitalWrite(LEDS[3], LOW);
}
