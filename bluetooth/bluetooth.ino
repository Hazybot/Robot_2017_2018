#include <SoftwareSerial.h>

SoftwareSerial mySerial(A0, A1);
void setup() {

  pinMode(13, OUTPUT);
  
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {

  //Serial.println(mySerial.available());
  if (mySerial.available()){
    
  
    char c = mySerial.read();
    Serial.println(c);
   
    if(c =='1') {
      digitalWrite(13, HIGH);
    }
    
    if(c == '0'){
      digitalWrite(13, LOW);
    }
    
    delay(50);
  }
}

