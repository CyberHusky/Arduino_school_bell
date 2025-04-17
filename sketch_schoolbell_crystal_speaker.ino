#include <SoftwareSerial.h>
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h> // бібліотека для mp3 плеєра
#include "DS3231.h" // RTC бібліотека, для "real time clock"

// ====== Objects ======
SoftwareSerial speaker(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

DS3231 clock;
RTCDateTime dt;


// ===== Global Variables ======
char weekDay[][4] = {"Mon","Tue","Wed","Thu","Fri",};

String times_bell_vivtorok[] = {"9:0:0", "9:40:0", "10:10:0", "10:50:0", "11:0:0", "11:35:0", "11:50:0", "12:25:0", "13:0:0", "13:35:0", "14:30:0", "15:10:0", "16:25:0", "17:0:0", "17:10:0", "17:45:0"};
String pre_times_bell_vivtorok[] = {"9:35:0", "10:45:0", "11:45:0", "12:20:0", "13:40:0", "14:40:0", "15:40:0", "16:40:0", "17:40:0"};

String times_bell_sereda[] = {"16:20:0", "17:0:0", "17:10:0", "17:50:0"};
String pre_times_bell_sereda[] = {"16:55:0", "17:45:0"};

String times_bell_chetver[] = {"9:0:0", "9:40:0", "10:10:0", "10:50:0", "11:0:0", "11:40:0", "11:50:0", "12:25:0", "13:0:0", "13:35:0", "14:30:0", "15:5:0"};
String pre_times_bell_chetver[] = {"9:35:0", "10:45:0", "11:35:0", "12:20:0", "13:30:0", "15:0:0"};


// ====== SETUP ======
void setup() {

// ====== Налаштування годинника ======

// -- запускати лише разово для синхронізації часу! --
  //my_clock_set(); // разово синхронізує час і додає 11 сек для точності
  
  //Serial.println("set time!");
  //clock.setDateTime(__DATE__, __TIME__); // запускаємо разово, коли треба синхронізувати час
  //dt = clock.convertStringToDateTime(__DATE__, __TIME__);
  //dt = addSeconds(dt, 13);  // додали 13 секунд
  //clock.setDateTime(dt);
// --

// ====== Налаштування ======
  Serial.begin(9600);
  //Wire.begin();        // Ініціалізація I2C
  clock.begin();         // Якщо бібліотека це підтримує

  speaker.begin(9600);
  speaker.listen();    

  if (!myDFPlayer.begin(speaker)) {  // Для налаштування і звʼязку з mp3 платою
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection of RX/TX in speaker!"));
    Serial.println(F("2.Please insert or reinsert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

// ====== Налаштування звука ======

  myDFPlayer.volume(25);      // Гучність. Значення від 0 до 30
  //myDFPlayer.volumeUp();    // Підвищення гучності
  //myDFPlayer.volumeDown();
  //Serial.println("Let's play 1 music!");
  //myDFPlayer.play(1);       // Відтворення першого mp3 файла для тесту
  //myDFPlayer.enableLoop();
  //myDFPlayer.loop(2);  
  //myDFPlayer.disableLoop();
  //myDFPlayer.pause();




// ====== Початок роботи ======

  Serial.println("Let's begin!");
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

  String str_hour   = String(dt.hour,DEC);
  String str_minute = String(dt.minute,DEC);
  String str_second = String(dt.second,DEC);
  String str_time_now = str_hour+":"+str_minute+":"+str_second;
   
  
  for (int i = 0; i < (sizeof(times_bell_vivtorok) / sizeof(times_bell_vivtorok[0])); i++){
    //if (strcmp(times_bell[i].c_str(), str_time_now.c_str()) == 0 && (dt.dayOfWeek == 1 || dt.dayOfWeek == 2 || dt.dayOfWeek == 3 || dt.dayOfWeek == 4 || dt.dayOfWeek == 5) ){
    if ((strcmp(times_bell_vivtorok[i].c_str(), str_time_now.c_str())) == 0 && (dt.dayOfWeek == 2)){
      Serial.println("Play music");
      myDFPlayer.play(1);
      //play_sound();
    }
  }
  for (int i = 0; i < (sizeof(times_bell_sereda) / sizeof(times_bell_sereda[0])); i++){
    if ((strcmp(times_bell_sereda[i].c_str(), str_time_now.c_str())) == 0 && (dt.dayOfWeek == 3)){
      Serial.println("Play music");
      myDFPlayer.play(1);
      //play_sound();
    }    
  }

  for (int i = 0; i < (sizeof(times_bell_chetver) / sizeof(times_bell_chetver[0])); i++){
    if ((strcmp(times_bell_chetver[i].c_str(), str_time_now.c_str())) == 0 && (dt.dayOfWeek == 4)){
      Serial.println("Play music");
      myDFPlayer.play(1);
      //play_sound();
    }  
  }

/* // оригінальний варіант
  for (int i = 0; i < (sizeof(pre_times_bell) / sizeof(pre_times_bell[0])); i++){
    if (strcmp(pre_times_bell[i].c_str(), str_time_now.c_str()) == 0 && (dt.dayOfWeek == 1 || dt.dayOfWeek == 2 || dt.dayOfWeek == 3 || dt.dayOfWeek == 4 || dt.dayOfWeek == 5) ){
      Serial.println("Play music");
      //myDFPlayer.play(1);
      //play_short_sound();
    }
    
  }
*/

}

// Синхронізує час і додає ще 11 секунд
void my_clock_set(){
  int hour, minute, second;
  clock.setDateTime(__DATE__, __TIME__);
  sscanf(__TIME__, "%d:%d:%d", &hour, &minute, &second);
  second += 11;
  if (second >= 60) {
    second -= 60;
    minute++;
    if (minute >= 60) {
      minute = 0;
      hour++;
      if (hour >= 24) hour = 0;
    }
  }

  // Розбір дати
  char monthStr[4];
  int day, year, month = 0;
  sscanf(__DATE__, "%s %d %d", monthStr, &day, &year);
  const char* months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
  for (int i = 0; i < 12; i++) {
    if (strncmp(monthStr, months[i], 3) == 0) month = i + 1;
  }

  clock.setDateTime(year, month, day, hour, minute, second);
  Serial.println("RTC синхронізовано з +11 секунд");

}