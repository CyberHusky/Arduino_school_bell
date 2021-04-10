#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "DS3231.h"
#include <Wire.h>
#include <OLED_I2C.h>

// ====== Objects ======
OLED  myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];
//extern uint8_t MediumNumbers[];
//extern uint8_t BigNumbers[];

SoftwareSerial speaker(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

DS3231 clock;
RTCDateTime dt;


// ===== Global Variables ======
char weekDay[][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};





// ====== SETUP ======
void setup() {

  Serial.begin(9600);
  
  speaker.begin(9600);
  speaker.listen();    // wait for speaker-arduino conversation

  if (!myDFPlayer.begin(speaker)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection of RX/TX in speaker!"));
    Serial.println(F("2.Please insert or reinsert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myOLED.begin();
  myOLED.setFont(SmallFont);


  Wire.begin();
  clock.setDateTime(__DATE__, __TIME__);
  
  myDFPlayer.volume(15);      //Set volume value. From 0 to 30
  //myDFPlayer.volumeUp();    //Volume Up
  //myDFPlayer.volumeDown();
  //myDFPlayer.play(1);       //Play the first mp3
  //myDFPlayer.enableLoop();
  //myDFPlayer.loop(2);  
  //myDFPlayer.disableLoop();
  //myDFPlayer.pause();
}



// ====== LOOP ======
void loop() {
  dt = clock.getDateTime();

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  // 2021-10-04 13:49:00


  myOLED.clrScr();
  //myOLED.print({"Water level " + ver}, CENTER, 0);
  //myOLED.print(Plant1_info, LEFT, 16); 
  myOLED.update();

  
}
