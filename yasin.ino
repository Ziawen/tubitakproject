#define trafikisik_kirmizi 5
#define trafikisik_sari 4
#define trafikisik_yesil 3
#define yayaisik_kirmizi 7
#define yayaisik_yesil 6

unsigned long oldTime;
unsigned long newTime;
int zatenbasildi = 0; //Spam Koruması


void setup()
{
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(2600);
  digitalWrite(trafikisik_yesil,1);
  digitalWrite(yayaisik_kirmizi,1);
  oldTime=millis();
  newTime=millis();
}

void loop()
{
  
  newTime = millis();

  char deger = digitalRead(2);
  
if(deger==1){
    
    if(zatenbasildi==0){
      
      Serial.println(newTime);
      newTime-=oldTime;
        if(newTime>3000){
          zatenbasildi=1;
          oldTime=millis();
          kirmiziisik();
        }else{
          Serial.println(" Bekleme ");
        }
      
    }
 }
}


void yesilisik(){
  digitalWrite(trafikisik_kirmizi,1);
  for(int i=1; i<=3; i++){
  digitalWrite(yayaisik_yesil,1);
  delay(1000);
  digitalWrite(yayaisik_yesil,0);
   delay(1000);
   }
  delay(1000);
  digitalWrite(yayaisik_kirmizi,1);
  delay(5000);
  digitalWrite(trafikisik_sari,1);
  delay(2000);
  digitalWrite(trafikisik_sari,0);
  digitalWrite(trafikisik_kirmizi,0);
  digitalWrite(trafikisik_yesil,1);
  oldTime=millis();
  zatenbasildi=0;
}


void kirmiziisik(){
 digitalWrite(yayaisik_kirmizi,1);
  for(int i=1; i<=3; i++){
  digitalWrite(trafikisik_yesil,1);
  delay(1000);
  digitalWrite(trafikisik_yesil,0);
   delay(1000);
   }
  digitalWrite(trafikisik_sari,1);
  delay(3000);
  digitalWrite(trafikisik_sari,0);
  digitalWrite(trafikisik_kirmizi,1);
  digitalWrite(yayaisik_yesil,1);
  digitalWrite(yayaisik_kirmizi,0);
  delay(15000);
  yesilisik();
}
