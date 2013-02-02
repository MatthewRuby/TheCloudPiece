
int r0 = 0;      //value select pin at the 4051 (s0)
int r1 = 0;      //value select pin at the 4051 (s1)
int r2 = 0;      //value select pin at the 4051 (s2)

int row = 0;     // storeing the bin code
int count = 0;    // just a count
unsigned char dataOut[8];

int  bin [] = {000, 1, 10, 11, 100, 101, 110, 111};//bin = binär, some times it is so easy

void setup(){

  pinMode(2, OUTPUT);    // s0

  pinMode(3, OUTPUT);    // s1

  pinMode(4, OUTPUT);    // s2

  Serial.begin(9600);

}

void loop () {
  
  digitalWrite(5, 0);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  
  Serial.println(analogRead(A0));
  
/*
  if(Serial.available()){
    byte value = Serial.read();
      
    if(value == 'a'){ // good
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      Serial.println('1');
    }
    if(value == 'b'){ // good
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      Serial.println('2');
    }
    if(value == 'c'){ // bad
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      Serial.println('3');
    }
    if(value == 'd'){ // bad
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 0);
      Serial.println('4');
    }
    if(value == 'e'){ // good
      digitalWrite(2, 0);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      Serial.println('5');
    }
    if(value == 'f'){ // good
      digitalWrite(2, 1);
      digitalWrite(3, 0);
      digitalWrite(4, 1);
      Serial.println('6');
    }
    if(value == 'g'){ // bad
      digitalWrite(2, 0);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      Serial.println('7');
    }
    if(value == 'h'){ // bad
      digitalWrite(2, 1);
      digitalWrite(3, 1);
      digitalWrite(4, 1);
      Serial.println('8');
    }
  }
*/
}
