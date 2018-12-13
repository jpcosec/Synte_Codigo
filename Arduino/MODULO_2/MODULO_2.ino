
#include <Arduino.h>
#include <TM1637Display.h>
#include <Encoder.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

int sensorPin = A0;    // select the input pin for the potentiometer
int red = A9;
int green = A8;
int blue = A7;
Encoder myEnc(5,6);




// The amount of time (in milliseconds) between tests
#define TEST_DELAY   200

const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
  };

TM1637Display display(CLK, DIO);
int sensorvalue=0; 
void setup()
{

  display.setBrightness(0x0f);
  Serial.begin(9600);
}

void setBrillo(int brillo){
  analogWrite(red,brillo);
  analogWrite(blue,brillo);
  analogWrite(green,brillo);
}

void setColor(int r, int g, int b){
  analogWrite(red,r);
  analogWrite(blue,b);
  analogWrite(green,g);
}

void setPreColor(int i){
  if(i==1){
    analogWrite(red,0);
    analogWrite(blue,256);
    analogWrite(green,256);
  }
  else if(i==2){
    analogWrite(red,256);
    analogWrite(blue,0);
    analogWrite(green,256); 
  }
  else if(i==3){
    analogWrite(red,256);
    analogWrite(blue,256);
    analogWrite(green,0); 
  }
  else{
    analogWrite(red,0);
    analogWrite(blue,0);
    analogWrite(green,0); 
  }
}

void setMasterColor(int i, int val){
  int k = map(val,0,1024,256,0);
  
  if(i==1){
    analogWrite(red,k);
    analogWrite(blue,256);
    analogWrite(green,256);
  }
  else if(i==2){
    analogWrite(red,256);
    analogWrite(blue,k);
    analogWrite(green,256); 
  }
  else if(i==3){
    analogWrite(red,256);
    analogWrite(blue,256);
    analogWrite(green,k); 
  }
  else{
    analogWrite(red,k);
    analogWrite(blue,k);
    analogWrite(green,k); 
  }
}



void loop()
{

  sensorvalue = analogRead(sensorPin);
  
  display.showNumberDec(int(myEnc.read())/4, true);
  setMasterColor((int(myEnc.read())/4)%4,sensorvalue);
  
  //setPreColor(map(sensorvalue,0,1014,0,4));
  delay(TEST_DELAY);

  
  

  
  

  //while(1);
}
