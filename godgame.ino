
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
//^-----ของจอ
#include <Ppop.h>
Ppop ppop("INNOYELLOW", "inno15yellow");


int counter;//มาเก้บแสดงคะแนน
int god_u;

void setup() {
  // put your setup code here, to run once:
  ppop.wifiConnect(5000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //เริ่มการใช้งานจอ
  display.clearDisplay();//ล้างจอ
  display.setTextSize(2);//เราจะให้ตัวอักษร Font Size เป็น 1 แล้วนะ
  display.setTextColor(WHITE);
  counter = 0;
  pinMode(D6, INPUT);
  pinMode(D5, OUTPUT);
  god_u = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(D6) == LOW){
    counter = counter + 1;
    delay(100);
  }

  if(counter >= 20){
    analogWrite(D5, 500);
    delay(100);
    analogWrite(D5, 0);
    delay(100);  
    analogWrite(D5, 700);
    delay(1000);
    analogWrite(D5, 0);
    delay(100);  
    //post lng facebook
    String response;
    ppop.postOneIntToIFTTT( "EVENT"  , "KEY", counter, response);
    //reset kanan
    counter = 0;
  }
  
  display.clearDisplay();
  display.setCursor(20,20);
  display.println(counter);
  display.display();

}

