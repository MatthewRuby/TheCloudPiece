int s0 = 2;
int s1 = 3;
int s2 = 4;

int r0 = 0;      //value select pin at the 4051 (s0)
int r1 = 0;      //value select pin at the 4051 (s1)
int r2 = 0;      //value select pin at the 4051 (s2)

int row = 0;     // storeing the bin code

unsigned char dataOut[8];

int count = 0;    // just a count

//int dataOut[8];

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

void setup(){

  pinMode(s0, OUTPUT);    // s0
  pinMode(s1, OUTPUT);    // s1
  pinMode(s2, OUTPUT);    // s2

  Serial.begin(9600);

}

void loop () {
/*
  if(Serial.available()){
    byte value = Serial.read();
    if(value == 'a'){
      for (int i = 0; i < 8; i++) {
        Serial.print(dataOut[i],DEC);
      } 
    }
  }
*/  /*
  if(Serial.available()){
    char c = Serial.read();
    if(c == 'a'){
      count = 0;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'b'){
      count = 1;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'c'){
      count = 2;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'd'){
      count = 3;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'e'){
      count = 4;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'f'){
      count = 5;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'g'){
      count = 6;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
    if(c == 'h'){
      count = 7;
      Serial.print(bin[count][0]);
      Serial.print(" - ");
      Serial.print(bin[count][1]);
      Serial.print(" - ");
      Serial.print(bin[count][2]);
      Serial.println(" - ");
    }
  }*/
  for (count = 0; count <= 7; count++) {

    // select the bit  
    r0 = bin[count][0];
    r1 = bin[count][1];   
    r2 = bin[count][2];

    digitalWrite(s0, r0);
    digitalWrite(s1, r1);
    digitalWrite(s2, r2);
    
    int v = analogRead(A0);
//    delay(10);
    if(v > 0){
      Serial.print(count);
      Serial.print("\t - \t");
      Serial.println(v);
    }
    
 //   dataOut[count] = analogRead(A0);
 //   delay(1);
   }
/*
  for (int i = 0; i < 4; i++) {
    
    row = bin[i];      
    r0 = row & 0x01;
    r1 = (row>>1) & 0x01;
    r2 = (row>>2) & 0x01;

    digitalWrite(2, r0);
    digitalWrite(3, r1);
    digitalWrite(4, r2);

    int v = analogRead(A0);
    
    if(v > 0){
      Serial.print(i);
      Serial.print("\t - \t");
      Serial.println(v);
    }
    delay(1);
//    dataOut[i] = analogRead(A0)/4;
  }
*/  
  

}
