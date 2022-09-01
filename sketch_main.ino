#include <SoftwareSerial.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h> // библиотека для mp3 плеера
#include "DS3231.h" // RTC библиотека, для "real time clock" - часы реального времени(дословно)
//#include <Wire.h> // 5 и 6-е строки для OLED дисплеев, библиотека занимает очень много места, так что временно убрали идею с олед.
//#include <OLED_I2C.h>//

// ====== Objects ======
//OLED  myOLED(SDA, SCL, 8);
//extern uint8_t SmallFont[];
//extern uint8_t MediumNumbers[];
//extern uint8_t BigNumbers[];

SoftwareSerial speaker(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

DS3231 clock;
RTCDateTime dt;


// ===== Global Variables ======
char weekDay[][4] = {"Mon","Tue","Wed","Thu","Fri",};

String times_bell[] = {"8:0:0", "8:45:0", "8:55:0", "9:40:0", "9:50:0", "10:35:0", "10:45:0", "11:30:0", "11:50:0", "12:35:0", "12:50:0", "13:35:0", "13:45:0", "14:30:0", "14:40:0", "15:25:0", "20:59:20"};


// ====== SETUP ======
void setup() {

  Serial.begin(9600);
  
  speaker.begin(9600);
  speaker.listen();    

  if (!myDFPlayer.begin(speaker)) {  //Использование библиотеки softwareSerial для связи с mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection of RX/TX in speaker!"));
    Serial.println(F("2.Please insert or reinsert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  //myOLED.begin();
  //myOLED.setFont(SmallFont);

  delay(10);

  Serial.println("set time!");
  //clock.setDateTime(__DATE__, __TIME__);


  
  myDFPlayer.volume(5);      //Установка громкости. Значения от 0 до 30
  //myDFPlayer.volumeUp();    //Повышение Громкости
  //myDFPlayer.volumeDown();
  Serial.println("Let's play 1 music!");
  //myDFPlayer.play(1);       //Воспроизведение первого и единственного mp3 файла
  //delay(23000);
  //myDFPlayer.enableLoop();
  //myDFPlayer.loop(2);  
  //myDFPlayer.disableLoop();
  //myDFPlayer.pause();

  Serial.println("Let's begin!");
  
}



// ====== LOOP ======
void loop() {

  dt = clock.getDateTime(); // все та же библиотека DS3231

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  Serial.println(dt.dayOfWeek);

  delay(1000);

  Serial.println("HEY!");
  //char str_hour[]   = dt.hour;
  String str_hour   = String(dt.hour,DEC);
  String str_minute = String(dt.minute,DEC);
  String str_second = String(dt.second,DEC);
  String str_time_now = str_hour+":"+str_minute+":"+str_second;
   
  
  for (int i = 0; i < (sizeof(times_bell) / sizeof(times_bell[0])); i++){
    //Serial.println(times_bell[i]);
    //Serial.println(str_time_now);
    
    if (strcmp(times_bell[i].c_str(), str_time_now.c_str()) == 0 && (dt.dayOfWeek == 1 || dt.dayOfWeek == 2 || dt.dayOfWeek == 3 || dt.dayOfWeek == 4 || dt.dayOfWeek == 5) ){
      Serial.println("Play music");
      myDFPlayer.play(1);
    }
    
  }



//String(year())
  //myOLED.clrScr();
  //myOLED.print({"Time:"});
  //myOLED.print(Plant1_info, LEFT, 16); 
  //myOLED.update();

  
}
