const int DATA_LENGTH = 6;

const int LATCH_PIN = 8;
const int CLOCK_PIN = 11;
const int DATA_PIN = 10;

unsigned char setupCode[] = {'a','b','c'};
unsigned char ceilingCode[] = {'d','e','f'};

int dataOut[] = {0,0,0};
int dataPacket[] = {0,0,0,0,0};

boolean bFound = false;
boolean stringComplete = false;

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


    if (stringComplete) {

    
      if(dataPacket[0] == 97 && dataPacket[4] == 97){
     
      Serial.print("Success - ");
      /* 
      Serial.print("0 = ");
      Serial.println(dataPacket[0]);
      
      Serial.print("1 = ");
      Serial.println(dataPacket[1]);
      
      Serial.print("2 = ");
      Serial.println(dataPacket[2]);
      
      Serial.print("3 = ");
      Serial.println(dataPacket[3]);
      
      Serial.print("4 = ");
      Serial.println(dataPacket[4]);
     */ 
      dataOut[2] = dataPacket[1];
      dataOut[1] = dataPacket[2];
      dataOut[0] = dataPacket[3];
      
      Serial.println(dataOut[0]);
      Serial.println(dataOut[1]);
      Serial.println(dataOut[2]);
      
      
      digitalWrite(LATCH_PIN, 0);

      shiftOut(DATA_PIN, CLOCK_PIN, dataOut[0]);
      shiftOut(DATA_PIN, CLOCK_PIN, dataOut[1]);
      shiftOut(DATA_PIN, CLOCK_PIN, dataOut[2]);
    
      digitalWrite(LATCH_PIN, 1);
      
      
    } else {
      /*
      Serial.print("Error - ");
      
      Serial.print("0 = ");
      Serial.println(dataPacket[0], DEC);
      
      Serial.print("1 = ");
      Serial.println(dataPacket[1], DEC);
      
      Serial.print("2 = ");
      Serial.println(dataPacket[2], DEC);
      
      Serial.print("3 = ");
      Serial.println(dataPacket[3], DEC);
      */
    }
    
    stringComplete = false;
    
    }
    
  }

} // END LOOP()

int numBytes = 0;
void serialEvent() {
  
  while (Serial.available()) {
    int incoming = Serial.read();

    dataPacket[numBytes] = incoming;
    numBytes++;

    if (incoming == '\n') {
      numBytes = 0;
      stringComplete = true;
    }
    
  }
}

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

