//===================================================================
void slideShowJWS() {
  get_float_time_parts(times[j], jamSholat, mntSholat);
  mntSholat += selisihWaktu;
  if (mntSholat >= 60) {
    mntSholat = 0;
    jamSholat++;
  }
  if (j == 8) {
    get_float_time_parts(times[0], jamSholat, mntSholat);
    mntSholat += selisihWaktu;
    if (mntSholat < 10) {
      mntSholat = 60 - mntSholat;
      jamSholat--;
    }
    else {
      mntSholat = mntSholat - 10 ;
    }
  }
  tampilJWS(j, jamSholat, mntSholat);
}

//===================================================================
void realTimeScanJWS() {
  for (i = 0; i < 7; i++) {
    DateTime now = rtc.now();
    if (i == 1 or i == 4) {
      i++;
    }
    get_float_time_parts(times[i], jamSholat, mntSholat);
    mntSholat += selisihWaktu;
    if (mntSholat >= 60) {
      mntSholat = 0;
      jamSholat++;
    }
    Serial.println(i);
    if (jamSholat == now.hour() && mntSholat == now.minute()) {
      alarmJWS(i, jamSholat, mntSholat);
    }
  }
}

//===================================================================
void alarmJWS(byte jws, byte _jam, byte _mnt) {
  String alarmText = " Waktu Sholat ";
  byte dBuzz = 1;
  DateTime now = rtc.now();
  resetHoldTime();
  lcd.clear();
  while (jedaAdzan >= mntTunggu) {
    now = rtc.now();
    int disp = now.second() % 2;
    if (jws == 0) {                                 // Alarm Subuh
      if (disp == 1) {
        iconMasjidLCD();
        lcd.setCursor(1, 0);
        lcd.print(alarmText);
        tampilJWS(0, _jam, _mnt);
      }
      else {
        lcd.clear();
      }
    }

    else if (jws == 2) {                                 // Alarm Dhuhur
      if (disp == 1) {
        iconMasjidLCD();
        lcd.setCursor(1, 0);
        lcd.print(alarmText);
        tampilJWS(2, _jam, _mnt);
      }
      else {
        lcd.clear();
      }
    }

    else if (jws == 3) {                                 // Alarm Ashar
      if (disp == 1) {
        iconMasjidLCD();
        lcd.setCursor(1, 0);
        lcd.print(alarmText);
        tampilJWS(3, _jam, _mnt);
      }
      else {
        lcd.clear();
      }
    }

    else if (jws == 5) {                                 // Alarm Maghrib
      if (disp == 1) {
        iconMasjidLCD();
        lcd.setCursor(1, 0);
        lcd.print(alarmText);
        tampilJWS(5, _jam, _mnt);
      }
      else {
        lcd.clear();
      }
    }

    else if (jws == 6) {                                 // Alarm Isya
      if (disp == 1) {
        iconMasjidLCD();
        lcd.setCursor(1, 0);
        lcd.print(alarmText);
        tampilJWS(6, _jam, _mnt);
      }
      else {
        lcd.clear();
      }
    }

    if (disp == 1) {
      digitalWrite(Buzzer, dBuzz);
    }
    else {
      digitalWrite(Buzzer, LOW);
    }
    if (tDtk >= 20 or mntTunggu > 0) {
      dBuzz = 0;
    }
    tHold.update();
  }
}








