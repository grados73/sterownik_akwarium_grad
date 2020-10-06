#include <Adafruit_GFX.h> // biblioteka do wyswietlacza
#include <Adafruit_SSD1331.h> // biblioteka do wyswietlacza
#include <SPI.h>
#include "DHT.h"

// definicja pinów wyswietlacza
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

#define DHT11_PIN 2
DHT dht;

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

int wilgotnosc  = 0;
int temperatura = 0;
int poprzednia_temperatura = 0;
int poprzednia_wilgotnosc = 0;

void setup() {
  display.begin();
  display.fillScreen(RED);
  delay(200);
  display.fillScreen(BLACK);
  display.setCursor(20,5);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("Hello");
  
  Serial.begin(9600);
  dht.setup(DHT11_PIN);
  
 }
void loop() 
{
  poprzednia_temperatura = temperatura;
  poprzednia_wilgotnosc = wilgotnosc;
  wilgotnosc = dht_wilgotnosc();
  temperatura = dht_temperatura();
  if((poprzednia_temperatura != temperatura or poprzednia_wilgotnosc != wilgotnosc)and (temperatura <= 200 and wilgotnosc <= 100 )){
  wyswietl_wilgotnosc_temp(wilgotnosc, temperatura);
}
  delay(1000);

                
}

int dht_wilgotnosc(){
    int wilgotnosc = dht.getHumidity();
    if (dht.getStatusString() == "OK") return wilgotnosc;
}

int dht_temperatura(){
    int temperatura = dht.getTemperature();
    if (dht.getStatusString() == "OK") return temperatura;
}
void wyswietl_wilgotnosc_temp( int wilgotnosc, int temperatura){
     display.fillScreen(BLUE);
     display.setTextColor(WHITE);     
     display.setCursor(10,5);
     display.print("W="); 
     display.setCursor(40,5);
     display.print(wilgotnosc);
     display.setCursor(10,25);
     display.print("T="); 
     display.setCursor(40,25);
     display.setTextColor(WHITE);
     display.print(temperatura);  
}
