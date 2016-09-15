
#include "Time.h"

#define LED 6

#define A A4
#define B A2
#define C 10
#define D 8
#define E 7
#define J A3 // Это F
#define G 11

#define CA2 A0
#define CA1 13
#define CA3 A1

#define DP 9      // Точка

const int segs[7] = { 
  A, B, C, D, E, J, G };

const byte numbers[10] = {  
  0b1000000, 
  0b1111001, 
  0b0100100, 
  0b0110000, 
  0b0011001, 
  0b0010010,
  0b0000010, 
  0b1111000, 
  0b0000000, 
  0b0010000 };

long previousMillis = 0; 
long interval = 1000;
unsigned long currentMillis;

int thousands = 0;
int hundreds = 0;
int tens = 0;
int hours = 0;

byte nowMin = 1;

void setup() {                

  pinMode(LED, OUTPUT);  

  pinMode(13,OUTPUT);  // Digital 1
  pinMode(A0,OUTPUT);  // Digital 2  
  pinMode(A1,OUTPUT);  // Digital 3

  pinMode(A4,OUTPUT); // SEG A
  pinMode(A2,OUTPUT); // SEG B
  pinMode(10,OUTPUT); // SEG C
  pinMode(8,OUTPUT);  // SEG D
  pinMode(7,OUTPUT);  // SEG E
  pinMode(A3,OUTPUT); // SEG F
  pinMode(11,OUTPUT); // SEG G

  pinMode(DP,OUTPUT);  // DP

  digitalWrite(LED,HIGH);

  setTime(0,0,0,1,1,2016);

}
void loop() {

  currentMillis = millis();

  lightDigit3(numbers[hundreds]);
  delay(5);
  lightDigit2(numbers[tens]);
  delay(5);

  if (hour() == 0) {
    if (minute() < 10) {
      lightDigit1(numbers[minute()],nowMin);
    } 
    else {
      lightDigit1(numbers[hours],0);
    }
  } 
  else {
    lightDigit1(numbers[hours],0);
  }
  delay(5);

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (nowMin == 1) nowMin = 0; 
    else nowMin = 1;

    if (digitalRead(LED) == 1) { 
      digitalWrite(LED,LOW); 
    } 
    else { 
      digitalWrite(LED,HIGH); 
    }
    hundreds = second()%10;
    tens = second()/10;
    hours = hour();
    if (hours > 9) {   
      setTime(0,0,0,1,1,2016);
    }
  }
}

void lightDigit1(byte number,byte point) {
  digitalWrite(CA1,HIGH);
  digitalWrite(CA2,LOW);
  digitalWrite(CA3,LOW);  
  if (point == 1) {
    digitalWrite(DP, HIGH);  
  } 
  else {
    digitalWrite(DP, LOW);  
  }    
  lightSegments(number);
}

void lightDigit2(byte number) {
  digitalWrite(CA1,LOW);
  digitalWrite(CA2,HIGH);
  digitalWrite(CA3,LOW);    
  digitalWrite(DP, HIGH);  
  lightSegments(number);
}

void lightDigit3(byte number) {
  digitalWrite(CA1,LOW);
  digitalWrite(CA2,LOW);
  digitalWrite(CA3,HIGH);
  digitalWrite(DP, HIGH);  
  lightSegments(number);
}

void lightSegments(byte number) {
  for (int i = 0; i < 7; i++) {
    int bit = bitRead(number, i);
    digitalWrite(segs[i], bit);
  }
}









