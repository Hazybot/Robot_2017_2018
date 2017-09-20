#include <LedControl.h>

#define NB_MATRIX 4 

LedControl lc=LedControl(12,11,10,4);

void shutdownAll(bool state){
  for(int i = 0 ; i < NB_MATRIX ; i++){
    lc.shutdown(i, state);
  }
}

//Set intensity of all matrix by value between 0 and 15
void setBrightnessAll(int intensity){
  for(int i = 0 ; i < NB_MATRIX ; i++){
    lc.setIntensity(i, intensity);
  }
}

void clearAll(){
  for(int i = 0 ; i < NB_MATRIX ; i++){
    lc.clearDisplay(i);
  }
}

void printZero(int addr){
  lc.setColumn(addr, 2, B00111100);
  lc.setColumn(addr, 3, B01000010);
  lc.setColumn(addr, 4, B01000010);
  lc.setColumn(addr, 5, B00111100);
}

void printOne(int addr){
  lc.setColumn(addr, 3, B00100010);
  lc.setColumn(addr, 4, B01111110);
  lc.setColumn(addr, 5, B00000010);
}

void printTwo(int addr){
  lc.setColumn(addr, 2, B00100010);
  lc.setColumn(addr, 3, B01000110);
  lc.setColumn(addr, 4, B01001010);
  lc.setColumn(addr, 5, B00110010);
}

void printThree(int addr){
  lc.setColumn(addr, 2, B00100010);
  lc.setColumn(addr, 3, B01000010);
  lc.setColumn(addr, 4, B01010010);
  lc.setColumn(addr, 5, B00101100);
}

void printFour(int addr){
  lc.setColumn(addr, 2, B00001000);
  lc.setColumn(addr, 3, B00011000);
  lc.setColumn(addr, 4, B00101000);
  lc.setColumn(addr, 5, B01111110);
}

void printFive(int addr){
  lc.setColumn(addr, 2, B01110100);
  lc.setColumn(addr, 3, B01010010);
  lc.setColumn(addr, 4, B01010010);
  lc.setColumn(addr, 5, B01001100);
}

void printSix(int addr){
  lc.setColumn(addr, 2, B00111100);
  lc.setColumn(addr, 3, B01010010);
  lc.setColumn(addr, 4, B01010010);
  lc.setColumn(addr, 5, B00001100);
}

void printSeven(int addr){
  lc.setColumn(addr, 2, B01000000);
  lc.setColumn(addr, 3, B01000110);
  lc.setColumn(addr, 4, B01011000);
  lc.setColumn(addr, 5, B01100000);
}

void printHeight(int addr){
  lc.setColumn(addr, 2, B00101100);
  lc.setColumn(addr, 3, B01010010);
  lc.setColumn(addr, 4, B01010010);
  lc.setColumn(addr, 5, B00101100);
}

void printNine(int addr){
  lc.setColumn(addr, 2, B00110000);
  lc.setColumn(addr, 3, B01001010);
  lc.setColumn(addr, 4, B01001010);
  lc.setColumn(addr, 5, B00111100);
}


void setup() {
  // put your setup code here, to run once:
  shutdownAll(false);
  setBrightnessAll(10);
  clearAll();
}

void loop() {
  // put your main code here, to run repeatedly:
  hour();
}
