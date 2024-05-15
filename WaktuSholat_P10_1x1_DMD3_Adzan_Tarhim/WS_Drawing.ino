// =========================================
// Drawing Content Block====================
// =========================================
void drawTarhim(int DrawAdd)
{
  // check RunSelector
   if (!dwDo(DrawAdd)) return;

 static uint16_t   lsRn;
  static uint16_t   ct;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 500) 
  { 
    lsRn = Tmr;
    if ((ct % 2) == 0)
    {
    
    fType(0);
    dwCtr(0, 0, "TARHIM");
    if (ct <= 2 )
    {digitalWrite(BUZZ, HIGH);}
    }
    else
    {digitalWrite(BUZZ, LOW);}
     
    fType(4);
    drawGreg_TS(8); // baris bawah 
    
{  
 DoSwap=true;
 ct++;
 }   
if ((Tmr-lsRn)>2000) 

{ dwDone(DrawAdd);
ct=0;
  }
}
azzan=false;
jumat=false; 
}

void drawAzzan(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;
  uint16_t           ct_limit = 360; //DEFAULT 18 harus angka genap TAMPILAN ADZAN( 480/2)/60 = 4 MENIT)
  static uint16_t    ct;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 500 and ct <= ct_limit)
  {
    lsRn = Tmr;
    if ((ct % 2) == 0)
    {      
      fType(0);
      dwCtr(0, 0, "ADZAN");
      fType(0);
      if (jumat) {
        dwCtr(0, 8, sholatN(8));
      }
      else      {
        dwCtr(0, 8, sholatN(SholatNow));
      }
      if (ct <= 4) {  //ct <= 4 BUNYI BEEP 3 x
      }
    }
    else {
      digitalWrite(BUZZ, LOW);
    }
    DoSwap = true;
    ct++;
  }
  if ((Tmr - lsRn) > 2000 and (ct > ct_limit))
  { dwDone(DrawAdd);
    ct = 0;
    digitalWrite(BUZZ, LOW);
  }
}

void drawIqomah(int DrawAdd)  
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  static int        ct;
  int               mnt, scd, cn_l ;
  char              locBuff[6];

  cn_l  = (Iqomah[SholatNow] * 60);  
  fType(0);
  if ((Tmr - lsRn) > 1000 and ct <= cn_l)
  {
    lsRn = Tmr;
    mnt = floor((cn_l - ct) / 60);
    scd = (cn_l - ct) % 60;
    if (mnt > 0) {
      sprintf(locBuff, "%02d:%02d", mnt, scd);
    } else {
      sprintf(locBuff, "-%02d", scd);      
    }
    fType(0);
    dwCtr(0, 0, "IQOMAH");
    fType(1);
    dwCtr(0, 8, locBuff);    
    if (ct > (cn_l - 2)) digitalWrite(BUZZ, HIGH);
    ct++;
    DoSwap = true;
  }
  if (ct > cn_l)
  {
    dwDone(DrawAdd);
    ct = 0;    
    digitalWrite(BUZZ, LOW);
  }
}


void drawSholat_S(int sNum, int c) // Box Sholah Time
{
  char  BuffTime[10];
  char  BuffShol[7];
  float   stime   = sholatT[sNum];
  uint8_t shour   = floor(stime);
  uint8_t sminute = floor((stime - (float)shour) * 60);
  uint8_t ssecond = floor((stime - (float)shour - (float)sminute / 60) * 3600); 
  sprintf(BuffTime, "%02d:%02d", shour, sminute);
  Disp.drawLine(3, 8, 28, 8); 
  fType(0); dwCtr(0, 0, sholatN(sNum));
  fType(0); dwCtr(0, 9, BuffTime);
  DoSwap = true;
}

void drawSholat(int DrawAdd)
{
  if (!dwDo(DrawAdd)) return;
  static uint8_t    x;
  static uint8_t    s; // 0=in, 1=out
  static uint8_t    sNum;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  uint8_t           c = 0; 
  uint8_t           first_sNum = 0;
  int               DrawWd = DWidth - c;

  if ((Tmr - lsRn) > 70)
  {
    if (s == 0 and x < (DrawWd / 2)) { x++; lsRn = Tmr; }
    if (s == 1 and x > 0) { x--;  lsRn = Tmr; }
  }

  if ((Tmr - lsRn) > 3000 and x == (DrawWd / 2)) { s = 1;  }
  if (x == 0 and s == 1){if (sNum < 7) {sNum++;}
    else
    {dwDone(DrawAdd); sNum = 0;}
    s = 0;
  }

  if (Prm.SI == 0) { first_sNum = 1;}
  else {first_sNum = 0;}
  if (Prm.SI == 0 and sNum == 0) {sNum = 1;}
  if (Prm.ST == 0 and sNum == 2) {sNum = 3;}
  if (Prm.SU == 0 and sNum == 3) {sNum = 4;}
  drawSholat_S(sNum, c);
  
  
  Disp.drawFilledRect(c, 0, c + DrawWd / 2 - x, 15, 0);
  Disp.drawFilledRect(DrawWd / 2 + x + c, 0, 32, 15, 0);
  //Disp.drawLine(DrawWd/2-x-1,0,DrawWd/2-x-1,15,0);
  //Disp.drawLine(DrawWd/2+x,0,DrawWd/2+x,15,0);  
  //Disp.drawLine(DrawWd/2-x-1,0,DrawWd/2-x-1,15,1);
  //Disp.drawLine(DrawWd/2+x,0,DrawWd/2+x,15,1);
  Disp.drawLine(15-x,0,-1,8,1);    // garis atas (/)
  Disp.drawLine(32,8,16+x+c,0,1); // garis atas (\)
  Disp.drawLine(15-x,15,-1,8,1);    // garis bawah (/)
  Disp.drawLine(32,8,16+x+c,15,1); // garis bawah (\)    
  Disp.drawCircle(16,8,x+c+3,1);  // lingkaran di tengah (O) 
   
}


void drawGreg_DS(uint16_t y)   //Draw Date
{
  char  Buff1[15];
  char  Buff2[5];
  sprintf(Buff1, "%02d-%02d", now.day(), (now.month())); 
  sprintf(Buff2, "%04d", now.year() ); 
  dwCtr(0, y, Buff1);
  dwCtr(0, y+8, Buff2);
  DoSwap = true;
}
void Jam(uint16_t y) 
{
  static uint16_t ss; 
  uint16_t          Tmr = millis();
  char BuffH[3];
  char BuffM[3];
  char BuffD[3];
  sprintf(BuffH, "%02d", now.hour());
  sprintf(BuffM, "%02d", now.minute());
  sprintf(BuffD, "%02d", now.second());
  fType(3);
  Disp.drawText(1, y, BuffH);
  fType(3);
  Disp.drawText(18, y, BuffM);
  //Disp.drawText(18, y, BuffD);
  if (Tmr - ss < 500 and y == 0) {
    Disp.drawFilledRect(15, 4, 16, 6,1);   // dot blink
    Disp.drawFilledRect(15, 10, 16, 12,1); // dot blink
  }
  if (Tmr - ss > 1000) ss = Tmr;

  DoSwap = true;
}

void drawGreg_TS(uint16_t y)   // Draw Time
{
  char  Buff[20];
  sprintf(Buff, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  dwCtr(0, y, Buff);
  DoSwap = true;
}

void anim_JG(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 55)   ///// TAMPIL JAM BESAR
  {
    if (s == 0 and y < 17) {lsRn = Tmr; y++; }
    if (s == 1 and y > 0) { lsRn = Tmr; y--; }
  }
  if ((Tmr - lsRn) > 10000 and y == 17) {s = 1;}
  if (y == 7) { }
  if (y == 0 and s == 1) {dwDone(DrawAdd); s = 0;}
  Jam(17 - y);
}

void anim_DT(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 100)   
  {
    if (s == 0 and y < 15) {lsRn = Tmr; y++; }
    if (s == 1 and y > 0) {lsRn = Tmr; y--; }
  }
  if ((Tmr - lsRn) > 10000 and y == 15) {s = 1;}
  if (y == 7) { }
  if (y == 0 and s == 1) { dwDone(DrawAdd); s = 0; }
 
  fType(0);  
  drawGreg_DS(y-15);
  
}

void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd)
{
  // check RunSelector
  static uint16_t   x;
  if (!dwDo(DrawAdd)) return;
  if (reset_x != 0) {x = 0; reset_x = 0;}


  static uint16_t   lsRn;
  int fullScroll = Disp.textWidth(msg) + DWidth;
  uint16_t          Tmr = millis();
  if ((Tmr - lsRn) > Speed)
  { lsRn = Tmr;
    if (x < fullScroll) {++x;}
    else {dwDone(DrawAdd); x = 0; return; }
    
    if (dDT == 1)
      {
      fType(1);     
      Disp.drawText(DWidth - x, 8, msg); //Atas
      fType(4);
      if (x <= 6) {drawGreg_TS(x - 6);}
      else if (x >= (fullScroll - 6))   {drawGreg_TS((fullScroll - x) - 6);}
      else {drawGreg_TS(0); }
      }
    else if (dDT == 2)
      {
      fType(4);
      if (x <= 6){drawGreg_TS(x - 6);}
      else if (x >= (fullScroll - 6))   {drawGreg_TS((fullScroll - x) - 6);}
      else  { drawGreg_TS(0); }
      
      fType(1);
      Disp.drawText(DWidth - x, 8 , msg);//Bawah
      }
    else
    {
      fType(1);
      Disp.drawLine(0, 2, 31, 2); 
      Disp.drawLine(0, 13, 31, 13); 
      Disp.drawText(DWidth - x, 4, msg);
    }
    DoSwap = true;
  }
}

//void blinkBlock(int DrawAdd)
//{
//  // check RunSelector
//  if (!dwDo(DrawAdd)) return;

//  static uint16_t   lsRn;
//  static uint16_t   ct, ct_l;
//  uint16_t          Tmr = millis();

//  if (jumat)       {
//    ct_l = Prm.JM * 60;
//  }
//  else            {
//    ct_l = Prm.SO * 60;
//  }
//  //    jumat =false;

//  if ((Tmr - lsRn) > 1000)
//  { lsRn = Tmr;

//    if ((ct % 2) == 0)
//    {

//      Disp.drawFilledRect(DWidth - 3, DHeight - 3, DWidth - 2, DHeight - 2);
//    }
//    DoSwap = true;
//    ct++;
//  }
//  if (ct > ct_l)
//  { dwDone(DrawAdd);
//    azzan = false;
//    jumat = false;
//    ct = 0;
//  }
//  Disp.drawText(1, 7, String(ct_l - ct));
//}

// =========================================
// Drawing Tools============================
// =========================================
boolean dwDo(int DrawAdd)
{ if (RunSel == DrawAdd) {
    return true;
  }
  else return false;
}

void dwDone(int DrawAdd)
{ RunFinish = DrawAdd;
  RunSel = 0;
}

void dwCtr(int x, int y, const char* Msg)
{ int   tw = Disp.textWidth(Msg);
  int   th = Disp.textHeight();
  int   c = int((DWidth - x - tw) / 2);
  Disp.drawFilledRect(x + c - 1, y, x + tw + c, y + th, 0);
  Disp.drawText(x + c, y, Msg);
}

//void Buzzer(uint8_t state)
//{
//  if (state == 1 and Prm.BZ == 1)
//  {
//    tone(BUZZ, 1000, 500); /// 500,400
//  }
//  else
//  {
//    noTone(BUZZ);
//  }
//}

void fType(int x)
{
  if (x == 0) Disp.setFont(Font0);
  else if (x == 1)    Disp.setFont(Font1);
  else if (x == 2)    Disp.setFont(Font2);
  else if (x == 3)    Disp.setFont(Font3);
  else Disp.setFont(Font4);
}
