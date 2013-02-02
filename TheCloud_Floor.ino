int s0 = 2;
int s1 = 3;
int s2 = 4;

int r0 = 0;      //value select pin at the 4051 (s0)
int r1 = 0;      //value select pin at the 4051 (s1)
int r2 = 0;      //value select pin at the 4051 (s2)

const int DATA_LENGTH = 3;

boolean bFound = false;
unsigned char floorCode[] = {'a','b','c'};

//int sensor[] = {A0,A1,A2,A3};
//int sensorValue[4];

const int ANALOG_VALS = 8;
unsigned char dataOut[ANALOG_VALS + 6];

int  bin [8][3] = {
  {0, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {1, 1, 0},
  {0, 0, 1},
  {1, 0, 1},
  {0, 1, 1},
  {1, 1, 1}
};

void setup() {
  pinMode(s0, OUTPUT);    // s0
  pinMode(s1, OUTPUT);    // s1
  pinMode(s2, OUTPUT);    // s2

  Serial.begin(9600);
}

void loop() {
  
  if(bFound == false){
    if (Serial.available() > 0) {
      char checkBuffer[3];
      Serial.readBytes(checkBuffer, 3);
      int bSetup = 0;
      for(int i = 0; i < 3; i++) {
        if(checkBuffer[i] == floorCode[i]){
          bSetup++;
        }
      }
      if(bSetup == 3) {
        bFound = true;
        Serial.write(floorCode, DATA_LENGTH);
      }
    }
  } else {

    for (int i = 0; i < ANALOG_VALS; i++) {

      r0 = bin[i][0];
      r1 = bin[i][1];   
      r2 = bin[i][2];
  
      digitalWrite(s0, r0);
      digitalWrite(s1, r1);
      digitalWrite(s2, r2);
    
      dataOut[i] = analogRead(A0);
    
    }
    
    if (Serial.available() > 0) {
 /*     
      char checkBuffer[DATA_LENGTH];
      Serial.readBytes(checkBuffer, DATA_LENGTH);
      
      int bFloor = 0;
      for(int i = 0; i < DATA_LENGTH; i++) {
        if(checkBuffer[i] == floorCode[i]){
          bFloor++;
        }
      }
      
      if(bFloor == 3) {
        Serial.write(dataOut, ANALOG_VALS);
      }
 */     
      Serial.write(dataOut, ANALOG_VALS + 6);
   
    }
 
  }
  

     
                
}
