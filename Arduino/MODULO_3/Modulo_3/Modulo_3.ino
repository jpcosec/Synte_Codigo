
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Encoder.h>

AudioPlaySdWav           playSdWav1;
AudioOutputAnalog           adc;
AudioConnection          patchCord1(playSdWav1, 0, adc, 0);
AudioConnection          patchCord2(playSdWav1, 1, adc, 1);

Encoder myEnc(5,6);
Bounce button0 = Bounce(23, 15);
//Bounce button2 = Bounce(2, 15);  // 15 = 15 ms debounce time

// Use these with the Teensy Audio Shield
//#define SDCARD_CS_PIN    10
//#define SDCARD_MOSI_PIN  7
//#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

void setup() {
  Serial.begin(9600);
  AudioMemory(8);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  myEnc.write(400);
  
  pinMode(23, INPUT_PULLUP);
  delay(1000);

}

int filenumber = 0;  // while file to play
int filenumberEnc = 0;


const char * filelist[6] = {
  "SDTEST1.WAV", "SDTEST0.WAV", "SDTEST2.WAV", "SDTEST3.WAV", "SDTEST4.WAV", "SDTEST5.WAV"
};


void loop() {
  
//  if (playSdWav1.isPlaying() == false) {
//    const char *filename = filelist[filenumber];
//    filenumber = filenumber + 1;
//    filenumberEnc = filenumber;
//    if (filenumber >= 6) filenumber = 0;
//    Serial.print("Start playing ");
//    Serial.println(filename);
//    playSdWav1.play(filename);
//    delay(10); // wait for library to parse WAV info
//  }

  filenumberEnc = (int(myEnc.read())/4)%6;
  
  // read pushbuttons
  button0.update();
  if (button0.fallingEdge()) {
    
    if (playSdWav1.isPlaying()){
      
      playSdWav1.stop();
      
    }
    
    else{      
          
        const char *filenameEnc = filelist[filenumberEnc];
        filenumber = filenumberEnc;
        if (filenumber >= 6) filenumber = 0;
        Serial.print("Start playing ");
        Serial.println(filenameEnc);
        playSdWav1.play(filenameEnc);
        delay(10); // wait for library to parse WAV info
          
    }
  }

  if (playSdWav1.isPlaying()){

    if(filenumberEnc!=filenumber){
    
    const char *filenameEnc = filelist[filenumberEnc];
    filenumber = filenumberEnc;
    if (filenumber >= 6) filenumber = 0;
    Serial.print("Start playing ");
    Serial.println(filenameEnc);
    playSdWav1.play(filenameEnc);
    delay(10); // wait for library to parse WAV info
    
    }
    
  }  
  
}
