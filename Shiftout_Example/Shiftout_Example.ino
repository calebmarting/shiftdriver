//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  uint16_t pos = 1;
  for(int i = 0; i<16; i++){
    writeBytes(pos);
    pos = pos<<1;
    delay(1000);
  }
  writeBytes(0);
  delay(1000);

  
  cycle(500);
  cycle(200);
  cycle(100);
  for(int i = 0; i<11; i++)
    cycle(50-i*4);
  for(int i = 0; i<10; i++)
    cycle(10);

}

void cycle(int sleep){
  uint16_t  pos=1;
  uint16_t toWrite = 0;
  for(int i = 0; i<8; i++){
    toWrite = toWrite | pos;
    writeBytes(toWrite);
    pos = pos<<1;
    delay(sleep);
  }
  pos = 1;
  for(int i = 0; i<8; i++){
    toWrite = toWrite ^ pos;
    writeBytes(toWrite);
    pos = pos<<1;
    delay(sleep);
  }
}

void writeBytes(uint16_t vals){

    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, vals>>8);
    shiftOut(dataPin, clockPin, MSBFIRST, (byte)vals);
    
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    

}
