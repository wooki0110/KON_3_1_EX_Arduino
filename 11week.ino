void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    char chr = Serial.read();
    
    if (chr>=0x41 && chr<=0x5a)
    {
      Serial.write(chr+0x20);
    }
    else if (chr>=0x61 && chr<=0x7a)
    {
      Serial.write(chr-0x20);
    }
    
    Serial.println();
  }
}
