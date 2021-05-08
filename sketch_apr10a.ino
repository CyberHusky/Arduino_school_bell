#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
//#include "DS3231.h"
#include <DS3232RTC.h> // https://github.com/JChristensen/DS3232RTC    
//#include <Wire.h>
//#include <OLED_I2C.h>

// ====== Objects ======
//OLED  myOLED(SDA, SCL, 8);
//extern uint8_t SmallFont[];
//extern uint8_t MediumNumbers[];
//extern uint8_t BigNumbers[];

//SoftwareSerial speaker(10, 11); // RX, TX
//DFRobotDFPlayerMini myDFPlayer;

//DS3231 clock;
//RTCDateTime dt;


// ===== Global Variables ======
char weekDay[][4] = {"Mon","Tue","Wed","Thu","Fri",};

String times_bell[] = {"8:0:0", "8:45:0", "8:55:0", "9:40:0", "9:50:0", "10:35:0", "10:45:0", "11:30:0", "11:50:0", "12:35:0", "12:50:0", "13:35:0", "13:45:0", "14:30:0", "14:40:0", "15:25:0"};

//times_bell = ['08:00:00','08:45:00','08:55:00', '09:40:00', '09:50:00', '10:35:00', '10:45:00', '11:30:00', '11:50:00', '12:35:00', '12:50:00', '13:35:00', '13:45:00', '14:30:00', '14:40:00', '15:25:00', ]
  
//hour() - 08 = 0
//minute() - 30 = 0
//second() - 00 = 0


// ====== SETUP ======
void setup() {

  Serial.begin(9600);
  
  //speaker.begin(9600);
  //speaker.listen();    // wait for speaker-arduino conversation
//
//  if (!myDFPlayer.begin(speaker)) {  //Use softwareSerial to communicate with mp3.
//    Serial.println(F("Unable to begin:"));
//    Serial.println(F("1.Please recheck the connection of RX/TX in speaker!"));
//    Serial.println(F("2.Please insert or reinsert the SD card!"));
//    while(true);
//  }
//  Serial.println(F("DFPlayer Mini online."));

  //myOLED.begin();
  //myOLED.setFont(SmallFont);


  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) Serial.println("Unable to sync with the RTC");
  else Serial.println("RTC has set the system time");
  
  setTime(7, 59, 50, 06, 05, 2021); 
  
  //myDFPlayer.volume(15);      //Set volume value. From 0 to 30
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
  
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(' ');
  Serial.print(day());
  Serial.print(' ');
  Serial.print(month());
  Serial.print(' ');
  Serial.print(year());
  Serial.println();
  delay(1000);

  Serial.println("HEY!");
  String str_hour   = String(hour(),DEC);
  String str_minute = String(minute(),DEC);
  String str_second = String(second(),DEC);
  int day = weekday();
  //Serial.println(day);
  String str_time_now = str_hour+":"+str_minute+":"+str_second;

  for (int i = 0; i < (sizeof(times_bell) / sizeof(times_bell[0])); i++){
    //Serial.println(times_bell[i]);
    Serial.println(str_time_now);
    
    if (strcmp(times_bell[i].c_str(), str_time_now.c_str()) == 0){
      Serial.println("Play music");
      //myDFPlayer.play(1);
    }
    
  }



//String(year())
  //myOLED.clrScr();
  //myOLED.print({"Time:"});
  //myOLED.print(Plant1_info, LEFT, 16); 
  //myOLED.update();

  
}


void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
