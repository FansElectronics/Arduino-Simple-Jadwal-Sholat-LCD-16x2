//===================================================================
void iconMasjidLCD() {
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(0, 1);
  lcd.write(byte(1));
  lcd.setCursor(15, 0);
  lcd.write(byte(0));
  lcd.setCursor(15, 1);
  lcd.write(byte(1));
}

//===================================================================
void tampilJAM() {
  DateTime now = rtc.now();
  byte _thn = now.year() - 2000;

  // Tampilan Jam
  lcd.setCursor(1, 0);
  lcd.print(konversi(now.hour()));
  lcd.setCursor(3, 0);
  if (digitalRead(Blink) == LOW) {
    lcd.print(':');
  }
  else {
    lcd.print(' ');
  }
  lcd.setCursor(4, 0);
  lcd.print(konversi(now.minute()));

  // Tampilan Tanggal
  lcd.setCursor(7, 0);
  lcd.print(konversi(now.day()));
  lcd.setCursor(9, 0);
  lcd.print('/');
  lcd.setCursor(10, 0);
  lcd.print(konversi(now.month()));
  lcd.setCursor(12, 0);
  lcd.print('/');
  lcd.setCursor(13, 0);
  lcd.print(konversi(_thn));
}

//===================================================================
void tampilJWS(byte _wkt, byte _jam, byte _mnt) {
  lcd.setCursor(1, 1);
  lcd.print(sholat[_wkt]);
  lcd.setCursor(10, 1);
  lcd.print(konversi(_jam));
  lcd.setCursor(12, 1);
  lcd.print(':');
  lcd.setCursor(13, 1);
  lcd.print(konversi(_mnt));
  tMain.update();
}
