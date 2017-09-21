#include <SoftwareSerial.h>
#include <Servo.h>

#include <fuzzy_table.h>
#include <PID_Beta6.h>

#include <Omni3WD.h>

//#include <SONAR.h>
#include <EEPROM.h>



// Motors

irqISR(irq1,isr1);
MotorWheel wheel1(9,8,6,7,&irq1);        // Pin9:PWM, Pin8:DIR, Pin6:PhaseA, Pin7:PhaseB

irqISR(irq2,isr2);
MotorWheel wheel2(10,11,14,15,&irq2);    // Pin10:PWM, Pin11:DIR, Pin14:PhaseA, Pin15:PhaseB

irqISR(irq3,isr3);
MotorWheel wheel3(3,2,4,5,&irq3);        // Pin3:PWM, Pin2:DIR, Pin4:PhaseA, Pin5:PhaseB

Omni3WD Omni(&wheel1,&wheel2,&wheel3);

Servo PinchServo;


int pulse1 = 0;
int pulse2 = 0;
int pulse3 = 0;

long calculDistanceAvance(long tilt){
    return 80*((double) tilt)/350;
}
long calculDistanceRecule(long tilt){
    return 80*((double) tilt)/350;
}
long calculDistanceTourne(long tilt){
    return 80*((float) tilt)/350;
}

long mouvement(long tilt1,long tilt2,long tilt3){
    long tiltAction1 = tilt1-pulse1;
    long tiltAction2 = tilt2-pulse2;
    long tiltAction3 = tilt3-pulse3;
    long valeur;
    if(tiltAction1 < 0 && tiltAction2 < 0 && tiltAction3 < 0 ){
        valeur = calculDistanceTourne((tiltAction1 + tiltAction2 + tiltAction3)/3);
    }
    else if(tiltAction1 > 0 && tiltAction2 > 0 && tiltAction3 > 0 ){
        valeur = calculDistanceTourne((tiltAction1 + tiltAction2 + tiltAction3)/3);
    }
    else if(tiltAction1 > 0 ){
        valeur = calculDistanceAvance((tiltAction1+tiltAction2)/2);
    }
    else{
        valeur = calculDistanceRecule((tiltAction1+tiltAction2)/2);
    }
    return valeur;
}

void getDistance(){
    char s[150];
    sprintf(s, "#%ld!", mouvement(wheel1.getCurrPulse(), wheel2.getCurrPulse(), wheel3.getCurrPulse()));
    Serial.print(s);
}

void forward(){
  Omni.setCarAdvance(200);
}

void backward(){
  Omni.setCarBackoff(200);
}

void turnLeft(){
  Omni.setCarRotateLeft(200);
}

void turnRight(){
  Omni.setCarRotateRight(200);
}

void translateLeft(){
  Omni.setCarLeft(200);
}

void translateRight(){
  Omni.setCarRight(200);
}

void stopR(){
  Omni.setCarSlow2Stop();
  Omni.delayMS(100);
}

void ouverturePince(){
  // ouverture de la pince
  // pour modifier la vitesse, il faut modifier le delay
  /*for(posPinchServo = 180; posPinchServo > 59; posPinchServo -=1)
  {
    PinchServo.write(posPinchServo);
    delay(8);
  }*/
  PinchServo.write(60);
}

void fermeturePince(){
  // fermeture de la pince
  // pour modifier la vitesse, il faut modifier le delay
  /*for(posPinchServo = 60; posPinchServo <= 180; posPinchServo +=1)
  {
    PinchServo.write(posPinchServo);
    delay(8);
  }*/
  PinchServo.write(180);
}


SoftwareSerial mySerial(A4, A5);

void setup() {
  TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz

  mySerial.begin(9600);

  //
  Omni.PIDEnable(0.46,0.2,0,10);
  PinchServo.attach(13);

  Serial.begin(19200);
  stopR();
  /*wheel3.runPWM(50, HIGH);
  wheel2.runPWM(50, LOW);*/
}

void loop() {
  
  if(mySerial.available()){
    
    char c = mySerial.read();

    Serial.println(c);

    switch(c){
      case 'f':
        forward();
        break;
      case 'r':
        turnRight();
        break;
      case 'l':
        turnLeft();
        break;
      case 'b':
        backward();
        break;
      case 'a':
        translateLeft();
        break;
      case 'e':
        translateRight();
        break;
      case 'o':
        translateRight();
        break;
      case 'c':
        translateRight();
        break;
      case 's':
        stopR();
        break;
    }
  }
  else{
    //stopR();
  }
  
  Omni.delayMS(100);

}
