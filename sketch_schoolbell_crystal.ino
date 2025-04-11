#include <SoftwareSerial.h>
#include <Arduino.h>
//#include <DFRobotDFPlayerMini.h> // библиотека для mp3 плеера
#include "DS3231.h" // RTC библиотека, для "real time clock" - часы реального времени(дословно)
#include <Wire.h> // 5 и 6-е строки для OLED дисплеев, библиотека занимает очень много места, так что временно убрали идею с олед.
//#include <OLED_I2C.h>//

#include "pitches.h"

// ====== Objects ======
//OLED  myOLED(SDA, SCL, 8);
//extern uint8_t SmallFont[];
//extern uint8_t MediumNumbers[];
//extern uint8_t BigNumbers[];

//SoftwareSerial speaker(10, 11); // RX, TX
//DFRobotDFPlayerMini myDFPlayer;

DS3231 clock;
RTCDateTime dt;


// ===== Global Variables ======
char weekDay[][4] = {"Mon","Tue","Wed","Thu","Fri",};

String times_bell[] = {"9:0:0", "9:45:0", "10:0:0", "10:45:0", "11:0:0", "11:45:0", "12:0:0", "12:45:0", "14:0:0", "14:45:0", "15:0:0", "15:45:0", "16:0:0", "16:45:0", "17:0:0", "17:45:0"};
String pre_times_bell[] = {"9:40:0", "10:40:0", "11:40:0", "12:40:0", "13:40:0", "14:40:0", "15:40:0", "16:40:0", "17:40:0"};

const int buzzer_pin = 2;

// Ноти мелодії (спрощений фрагмент)

/*
// beathles
int melody[] = {
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4
};

// Тривалість кожної ноти: 4 = чверть, 8 = восьма і т.д.
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 2, 4, 4, 2
};
// -------------
*/

/*
// Mario
int melody[] = {
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,
  NOTE_G5, 0, 0, NOTE_G4, 0,
  NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0,
  NOTE_A4, 0, NOTE_B4, 0, NOTE_AS4, NOTE_A4, 0,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, 0, NOTE_F5, NOTE_G5, 0,
  NOTE_E5, 0, NOTE_C5, NOTE_D5, NOTE_B4, 0
};

int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 4, 8, 8, 4,
  8, 8, 8, 8, 4, 4
};
//----------------
*/

// Minecraft sound
int melody[] = {
  NOTE_E4, NOTE_G4, NOTE_A4, 0, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_E4, NOTE_G4, NOTE_A4, 0, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, 0
};

int noteDurations[] = {
  8, 8, 4, 8, 8, 8, 8, 4,
  8, 8, 4, 8, 8, 8, 8, 4,
  8, 8, 8, 8, 4, 8, 8, 4,
  8, 8, 8, 8, 4, 4
};
// ------------

// ====== SETUP ======
void setup() {

  Serial.begin(9600);
  Wire.begin();        // Ініціалізація I2C
  clock.begin();       // Якщо бібліотека це підтримує

  //speaker.begin(9600);
  //speaker.listen();    
/*
  if (!myDFPlayer.begin(speaker)) {  //Использование библиотеки softwareSerial для связи с mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection of RX/TX in speaker!"));
    Serial.println(F("2.Please insert or reinsert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
*/

  //myOLED.begin();
  //myOLED.setFont(SmallFont);

  delay(10);

  //Serial.println("set time!");
  //clock.setDateTime(__DATE__, __TIME__); // запускаємо разово, коли треба синхронізувати час


/*
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
*/


// testing.... Mr. Freeman
  //play_sound();
  //play_short_sound();
}



// ====== LOOP ======
void loop() {
  //Serial.println("We are in the loop!");
  dt = clock.getDateTime(); // все та ж бібліотека DS3231

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
      //myDFPlayer.play(1);
      play_sound();
    }
  }

  for (int i = 0; i < (sizeof(pre_times_bell) / sizeof(pre_times_bell[0])); i++){
    if (strcmp(pre_times_bell[i].c_str(), str_time_now.c_str()) == 0 && (dt.dayOfWeek == 1 || dt.dayOfWeek == 2 || dt.dayOfWeek == 3 || dt.dayOfWeek == 4 || dt.dayOfWeek == 5) ){
      Serial.println("Play music");
      //myDFPlayer.play(1);
      play_short_sound();
    }
    
  }



//String(year())
  //myOLED.clrScr();
  //myOLED.print({"Time:"});
  //myOLED.print(Plant1_info, LEFT, 16); 
  //myOLED.update();

  
}

void play_sound(){
  for (int i = 0; i < sizeof(melody)/sizeof(int); i++) {
    int noteDuration = 900 / noteDurations[i];
    tone(buzzer_pin, melody[i], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(buzzer_pin);
  }  
}

void play_short_sound(){
  for (int i = 0; i < 3; i++) {
    tone(buzzer_pin, NOTE_A5, 300);   // 300 мс звучання
    delay(500);              // 200 мс пауза
  }
}