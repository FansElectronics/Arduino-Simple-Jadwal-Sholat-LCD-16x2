//===================================================================
// > Name    : Jadwal LCD 16x2 Simple + Button Setting
// > Writer  : Irfan Indra Kurniawan - FansElectronics.com
// > Version : 1.2

// Program ini dibuat untuk tujuan Pendidikan / Amal.
// Dilarang menjual belikan program ini, jika anda beriman.

//===================================================================
#include <LiquidCrystal.h>
#include <PrayerTimes.h>
#include <Timer.h>
#include <RTClib.h>

#define Buzzer    5
#define IR        3
#define bUP       A1
#define bDN       A3
#define bOK       A2
#define Blink     A3
#define ON        HIGH
#define OFF       LOW

//=============================================================
byte  jedaAdzan    = 1;                 // Waktu adzan (Menit)
byte  selisihWaktu = 0;                 // Selisi waktu sholat (Menit)
float lintang      = -7.98;             // Latitude
float bujur        = 112.62;            // Longitude
byte  zonaWaktu    = 7;                 // Zona Waktu

//=============================================================
String sholat[] = {"Subuh", " ", "Dhuhur", "Ashar", " ", "Maghrib", "Isya", " ", "Imsak"};
double times[sizeof(TimeName) / sizeof(char*)];
int jamSholat, mntSholat, tDtk, mntTunggu;
int jam, mnt, dtk, tgl, bln , thn;
int j, i, n, x;
int a, s, u;
bool setting = false;

//=============================================================
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
RTC_DS1307 rtc;
Timer tBlink, tMain, tHold ;

//=============================================================
byte puncak[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B01110,
  B01110,
};

byte tinggi[8] = {
  B11111,
  B01110,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
};

//===================================================================
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  rtc.begin();

  set_calc_method(ISNA);                   // Methode perhitungan mengikuti ISNA
  set_asr_method(Shafii);                  // Pendapat Imam Syafi'i
  set_high_lats_adjust_method(AngleBased); //
  set_fajr_angle(20);                      // Sudut Waktu Subuh
  set_isha_angle(18);                      // Sudut Waktu Isya

  pinMode(Blink, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(bOK, INPUT_PULLUP);
  pinMode(bUP, INPUT_PULLUP);
  pinMode(bDN, INPUT_PULLUP);

  digitalWrite(Buzzer, OFF);

  lcd.createChar(0, puncak);
  lcd.createChar(1, tinggi);

  tBlink.oscillate(Blink, 500, LOW);
  tMain.every(800, realTimeScanJWS);
  tMain.every(5000, intSlide);
  tHold.every(1000, holdTime);

  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2017, 10, 7, 11, 18, 30));
}

//===================================================================
void loop() {
  DateTime now = rtc.now();
  get_prayer_times(now.year(), now.month(), now.day(), lintang, bujur, zonaWaktu, times);
  int alm = now.second() % 2;
  if (alm == 1) {
    realTimeScanJWS();
  }
  
  if (digitalRead(bOK) == LOW) {                               // Tombol OK
    setting = true; 
  }
  
  while (setting) {
    menuSetting();
  }

  iconMasjidLCD();
  tampilJAM();
  slideShowJWS();

  if (!setting) {
    tBlink.update();
    tMain.update();
  }
}

//===================================================================
String konversi(int num) {
  if (num < 10) return "0" + String(num);
  else return String(num);
}

//===================================================================
void intSlide() {
  lcd.clear();
  if (n > 5) {
    n = 0;
  }
  switch (n) {
    case 0 : j = 8; break;  // Imsak
    case 1 : j = 0; break;  // Subuh
    case 2 : j = 2; break;  // Dhuhur
    case 3 : j = 3; break;  // Ashar
    case 4 : j = 5; break;  // Maghrib
    case 5 : j = 6; break;  // Isya'
  }
  n++;
}

//===================================================================
void holdTime() {
  tDtk++;
  if (tDtk >= 60) {
    mntTunggu++; tDtk = 0;
  }
}

//===================================================================
void resetHoldTime() {
  tDtk = 0; mntTunggu = 0;
}
