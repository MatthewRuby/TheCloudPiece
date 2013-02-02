const int DATA_LENGTH = 6;

const int LATCH_PIN = 8;
const int CLOCK_PIN = 11;
const int DATA_PIN = 10;

unsigned char setupCode[] = {'a','b','c'};
unsigned char ceilingCode[] = {'d','e','f'};

boolean bFound = false;

void setup() {
  Serial.begin(9600);

  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  
  digitalWrite(LATCH_PIN, 0);
  shiftOut(DATA_PIN, CLOCK_PIN, 0);
  shiftOut(DATA_PIN, CLOCK_PIN, 0);
  shiftOut(DATA_PIN, CLOCK_PIN, 0);
  digitalWrite(LATCH_PIN, 1);
  
} // END SETUP()


void loop(){
  
  if(bFound == false){
    
    if (Serial.available() > 0) {
      char checkBuffer[3];
      Serial.readBytes(checkBuffer, 3);
      int bSetup = 0;
      for(int i = 0; i < 3; i++) {
        if(checkBuffer[i] == setupCode[i]){
          bSetup++;
        }
      }
      if(bSetup == 3) {
        bFound = true;
        Serial.write(ceilingCode, 3);
      }
    }
    
    digitalWrite(LATCH_PIN, 0);
    shiftOut(DATA_PIN, CLOCK_PIN, 0);
    shiftOut(DATA_PIN, CLOCK_PIN, 0);
    shiftOut(DATA_PIN, CLOCK_PIN, 0);
    digitalWrite(LATCH_PIN, 1);
    
  } else {

    if (Serial.available() > 0) {
      char checkBuffer[DATA_LENGTH];
      Serial.readBytes(checkBuffer, DATA_LENGTH);
      
      int bCloud = 0;
      for(int i = 0; i < 3; i++) {
        if(checkBuffer[i] == ceilingCode[i]){
          bCloud++;
        }
      }
  
      if(bCloud == 3) {
        digitalWrite(LATCH_PIN, 0);
        shiftOut(DATA_PIN, CLOCK_PIN, checkBuffer[5]);
        shiftOut(DATA_PIN, CLOCK_PIN, checkBuffer[4]);
        shiftOut(DATA_PIN, CLOCK_PIN, checkBuffer[3]);
        digitalWrite(LATCH_PIN, 1);
      } else {
        
        digitalWrite(LATCH_PIN, 0);
        shiftOut(DATA_PIN, CLOCK_PIN, 0);
        shiftOut(DATA_PIN, CLOCK_PIN, 0);
        shiftOut(DATA_PIN, CLOCK_PIN, 0);
        digitalWrite(LATCH_PIN, 1);
        
      }
  
    }
    
  }
  
} // END LOOP()

// SHIFT REGISTER HELPER
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  for (int i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    } else {	
      pinState= 0;
    }
    digitalWrite(myDataPin, pinState); 
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0); 
  }
  digitalWrite(myClockPin, 0);
}

