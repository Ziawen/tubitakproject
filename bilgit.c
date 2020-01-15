/*
  Arduino -> Gösterge
  2  -> A
  3  -> B
  4  -> C
  5  -> D
  6  -> E
  7  -> F
  8      -> G
  VCC    -> Ortak Uç
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        7 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 19 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int role = 12;
int titremekoruma = 0;
int sayac = 0;
int giris = 0;
int cikis = 0;
int sensor = 4;
int lcdtitreme = 0;
int sensor2 = 3;
int hareketsensor = 10;
int mz = 0;
int mz2 = 0;
int hareket = 0;
int harekettitremekoruma = 0;
int i;
int sensorValue = 0;
int lamba = 11;
float  voltage;
void setup() {

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixe

  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(hareketsensor, INPUT);
  /* pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13,OUTPUT);*/
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Kisi Sayisi:");
  lcd.setCursor(0, 1);
  lcd.print("0");


}
unsigned long eskiZaman=0;
unsigned long yeniZaman;

void sayiyiYaz(byte sayi) {
  byte pin = 2;

  for (int i = 0; i < 7; i++) {
    pin ++;
  }

}

void mz_olc() {


  mz = digitalRead(sensor);
  mz2 = digitalRead(sensor2);
  hareket = digitalRead(hareketsensor);

}

void titreme_lcd() {

}
void loop() {
  mz_olc();
  Serial.print("mz 1 : ");
  Serial.println(mz);
  Serial.print("mz 2 : ");
  Serial.println(mz2);
  Serial.print("SAYACCCCC : ");
  Serial.println(sayac);
  Serial.print("Harekettttttttt :");
  Serial.println(hareket);
  if (sayac > 0) {
   yeniZaman = millis(); 

if (hareket == 1) {
          if (harekettitremekoruma == 0) {
          for (int i = 0; i < NUMPIXELS; i++) {


            pixels.setPixelColor(i, pixels.Color(150, 150, 150));

            pixels.show();

            delay(5);
            harekettitremekoruma = 1;
          }
  
        }
      } 


   if(yeniZaman-eskiZaman > 5000){
      if (hareket == 0) {
        pixels.show();
        pixels.clear();
        pixels.show();
        harekettitremekoruma = 0;
      } 
      else {
        if (harekettitremekoruma == 0) {
          for (int i = 0; i < NUMPIXELS; i++) {


            pixels.setPixelColor(i, pixels.Color(150, 150, 150));

            pixels.show();

            delay(5);
            harekettitremekoruma = 1;
          }
  
        }
      }
      
    eskiZaman = yeniZaman;

    }







    if (lcdtitreme == 0) {
      lcd.clear();
      lcd.print("Kisi Sayisi:");
      lcd.setCursor(0, 1);
      lcd.print(sayac);
      lcdtitreme = 1;
    }




    if (titremekoruma == 0) {
      for (int i = 0; i < NUMPIXELS; i++) {


        pixels.setPixelColor(i, pixels.Color(150, 150, 150));

        pixels.show();

        delay(5);
        titremekoruma = 1;
        
      }
  
    }
  } else {
    if (lcdtitreme == 0) {
      lcd.clear();
      lcd.print("Kisi Sayisi:");
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcdtitreme = 1;
    }
    titremekoruma = 0;
    pixels.show();
    pixels.clear();
    pixels.show();
  }
  /*
    for (int i = 0; i < 10; i ++) {
    sayiyiYaz(i);
    }  */

  while (mz2 == 0) {

    mz_olc();
    Serial.println("LDR 2 giris ");
    while (mz2 == 1) {
      Serial.println("ikinic while ");

      mz = digitalRead(sensor);
      mz2 = digitalRead(sensor2);
      //2 sn içerisinde 2. sensore(ldr=ışık sensörü) giriş yapılmazsa
      // başa döndüren kodlar.
      for (i = 0; i < 40; i++) {
        delay(50); //her 200ms de kkontrol ediliyor
        mz_olc();
        if (mz == 0) {
          break; //2 sn içerisinde 2. sensöre girilirse döngüden çık
        }
      }
      if (i == 40) {
        goto A1; //for döngüsü boyunca  2. sensöre girilmesdiyse- i 10 olacak- tüm while döngüsünden çok, başa dön
      }
      //Bu işlem kişi yarısından dönerse sayacı artma/azalma işlemine sokmaması için.

      while (mz == 0) {
        mz_olc();
        Serial.println("ucuncu while while ");
        lcdtitreme = 0;

        if (mz == 1)  {
          sayac++;
          delay(50);
          goto A1;
        }
      }

    }
  }
A1:

  while (mz == 0) {
    mz_olc();
    Serial.println("LDR 1 giris ");
    while (mz == 1) {
      Serial.println("LDR ikinic while ");
      mz_olc();



      for (i = 0; i < 40; i++) {
        delay(50);
        mz_olc();
        if (mz2 == 0) {
          break;
        }
      }
      if (i == 40) {
        goto A2;
      }
      while (mz2 == 0) {
        Serial.println(" LDR ucuncu while while ");
        lcdtitreme = 0;
        mz_olc();
        if (mz2 == 1)  {
          if (sayac > 0) {
            sayac--;
          } delay(50);
          goto A2;
        }
      }

    }
  }
A2:



  sayiyiYaz(sayac);
  Serial.print(sayac);
  if (sayac > 0)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
  }
  else
  {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }


}
