#include "Watchy_7_SEG.h"

#define DARKMODE false

void Watchy7SEG::drawWatchFace(){
    
    display.fillScreen(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setTextColor(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setFont(&FreeSansBold9pt7b);
    

    if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15500);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);     
         }

    // time adjustment end

    // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();   
          }


    int WTag, n;
    int16_t  x, y, xc, yc;
    uint16_t wc, hc;
    float radi = 0.0174532925;
    float m = currentTime.Minute;
    float h = currentTime.Hour;
    float mx = 90-m*6;
    float hx = ((h + (m / 60))*30) - 90;
    
    display.drawCircle(0, 100, 99, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawCircle(0, 100, 73, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawCircle(200, 100, 99, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawCircle(200, 100, 73, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

    for ( n = 1; n <= 12; n++) {
        x = 0 + 85 * sin((n * 30.0 - hx) * radi);
        y = 112 - 85 * cos((n * 30.0 - hx) * radi);
        display.getTextBounds(String(n), 100, 100, &xc, &yc, &wc, &hc);
        display.setCursor(x - wc / 2, y - hc / 2);
        if (x - wc / 2 >= 3) {
              display.println(n);
        }
    }
        
    for (int n = 0; n < 60; n = n + 5) {
        x = 200 + 85 * sin((n * 6 - mx) * radi);
        y = 112 - 85 * cos((n * 6 - mx) * radi);
        WTag = 60 - n;
        display.getTextBounds(String(WTag), 100, 100, &xc, &yc, &wc, &hc);
        display.setCursor(x - wc / 2, y - hc / 2);

        if ((x - wc / 2) + wc <= 196) {
            if (WTag == 60) {
                WTag = 0;
            }

            display.println(WTag);
        }
           
    }

    display.writeFastHLine(73, 100, 54, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
        
    String doW = dayShortStr(currentTime.Wday);
    display.getTextBounds(doW, 100, 100, &xc, &yc, &wc, &hc);
    display.setCursor(100 - wc / 2, 22 - hc / 2);
    display.println(doW);
    WTag = currentTime.Day;
    display.getTextBounds(String(WTag), 100, 100, &xc, &yc, &wc, &hc);
    display.setCursor(100 - wc / 2, 45 - hc / 2);
    display.println(WTag);
    String Monat = monthShortStr(currentTime.Month);
    display.getTextBounds(Monat, 100, 100, &xc, &yc, &wc, &hc);
    display.setCursor(100 - wc / 2, 190 - hc / 2);
    display.println(Monat);

    display.drawBitmap(13, 70, akku, 30, 20, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    float VBAT = getBatteryVoltage();
    int batLev = min<int>(100 - ((4.15 - VBAT) * 100), 100);
    batLev = max<int>(batLev, 0);
    display.getTextBounds(String(batLev), 100, 100, &xc, &yc, &wc, &hc);
    display.setCursor(25 - wc / 2, 125 - hc / 2);
    display.println(batLev);
    
    batLev = sensor.getCounter();
    display.drawBitmap(160, 67, steps, 19, 23, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.getTextBounds(String(batLev), 100, 100, &xc, &yc, &wc, &hc); 
    display.setCursor(170 - wc / 2, 125 - hc / 2);
    display.println(batLev);

    display.drawBitmap(0, 4, xlo, 27, 23, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(0, 174, xru, 27, 23, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(172, 4, xru, 27, 23, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.drawBitmap(172, 174, xlo, 27, 23, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    
}