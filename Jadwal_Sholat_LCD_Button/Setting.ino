//===================================================================
void displayRTC(byte _t, byte _b, byte _d, byte _j, byte _m) {
  // Tampilan Jam
  lcd.setCursor(1, 1);
  lcd.print(konversi(_j));
  lcd.setCursor(3, 1);
  lcd.print(':');
  lcd.setCursor(4, 1);
  lcd.print(konversi(_m));

  // Tampilan Tanggal
  lcd.setCursor(7, 1);
  lcd.print(konversi(_d));
  lcd.setCursor(9, 1);
  lcd.print('/');
  lcd.setCursor(10, 1);
  lcd.print(konversi(_b));
  lcd.setCursor(12, 1);
  lcd.print('/');
  lcd.setCursor(13, 1);
  lcd.print(konversi(_t));
}
//============================================================
void readRTC() {
  DateTime now = rtc.now();
  thn = now.year() - 2000;
  bln = now.month();
  tgl = now.day();
  jam = now.hour();
  mnt = now.minute();
}
//============================================================
void menuSetting() {
  DateTime now = rtc.now();
  readRTC();
  lcd.clear();
  int tahun;
  //============================================================
setJAM:
  lcd.setCursor(0, 0);
  lcd.print("    Set  JAM    ");
  displayRTC(thn, bln, tgl, jam, mnt);

  if (digitalRead(bOK) == LOW) {
    goto setMNT;
  }
  else if (digitalRead(bUP) == LOW) {
    jam++;
    if (jam >= 24) jam = 0;
  }
  else if (digitalRead(bDN) == LOW) {
    jam--; 
    if (jam < 0) jam = 23;
  }

  now = rtc.now();
  tahun = thn + 2000;
  rtc.adjust(DateTime(tahun, bln, tgl, jam, mnt, now.hour()));
  goto setJAM;

  //============================================================
setMNT:
  lcd.setCursor(0, 0);
  lcd.print("    Set  MNT    ");
  displayRTC(thn, bln, tgl, jam, mnt);

  if (digitalRead(bOK) == LOW) {
    goto setTGL;
  }
  else if (digitalRead(bUP) == LOW) {
    mnt++;
    if (mnt >= 60) mnt = 0;
  }
  else if (digitalRead(bDN) == LOW) {
    mnt--;
    if (mnt < 0) mnt = 59;
  }

  now = rtc.now();
  tahun = thn + 2000;
  rtc.adjust(DateTime(tahun, bln, tgl, jam, mnt, now.hour()));
  delay(300);

  goto setMNT;

  //============================================================
setTGL:
 
  lcd.setCursor(0, 0);
  lcd.print("    Set  TGL    ");
  displayRTC(thn, bln, tgl, jam, mnt);

  if (digitalRead(bOK) == LOW) {
    goto setBLN;
  }
  else if (digitalRead(bUP) == LOW) {
    tgl++;
    if (tgl >= 31) tgl = 0;
  }
  else if (digitalRead(bDN) == LOW) {
    tgl--;
    if (tgl < 0) tgl = 31;
  }

  now = rtc.now();
  tahun = thn + 2000;
  rtc.adjust(DateTime(tahun, bln, tgl, jam, mnt, now.hour()));
  delay(300);
  goto setTGL;

  //============================================================
setBLN:
  lcd.setCursor(0, 0);
  lcd.print("    Set  BLN    ");
  displayRTC(thn, bln, tgl, jam, mnt);

  if (digitalRead(bOK) == LOW) {
    goto setTHN;
  }
  else if (digitalRead(bUP) == LOW) {
    bln++;
    if (bln >= 12) bln = 1;
  }
  else if (digitalRead(bDN) == LOW) {
    bln--;
    if (bln < 0) bln = 12;
  }

  now = rtc.now();
  tahun = thn + 2000;
  rtc.adjust(DateTime(tahun, bln, tgl, jam, mnt, now.hour()));
  delay(300);
  goto setBLN;

  //============================================================
setTHN:
  lcd.setCursor(0, 0);
  lcd.print("    Set  THN    ");
  displayRTC(thn, bln, tgl, jam, mnt);

  if (digitalRead(bOK) == LOW) {
    goto setEND;
  }
  else if (digitalRead(bUP) == LOW) {
    thn++;
    if (bln > 50) thn = 18;
  }
  else if (digitalRead(bDN) == LOW) {
    thn--;
    if (bln < 18) thn = 50;
  }

  now = rtc.now();
  tahun = thn + 2000;
  rtc.adjust(DateTime(tahun, bln, tgl, jam, mnt, now.hour()));
  delay(300);
  goto setTHN;

setEND:
  setting = false;
  delay(500);
  lcd.clear();
}

