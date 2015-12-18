#include <DHT.h>
#define DHTPIN 7
#define NEOPIN 4
#define NUMPIXELS 8

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

float tempC;

int blueTemp= 0; int greenTemp= 0; int redTemp= 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
  strip.begin();
  dht.begin();

}

void loop()
{
tempC = dht.readTemperature(true);//read the value from the sensor
Serial.println(tempC);             //send the data to the computer

if(tempC<0){
  blueTemp = 255;
  }
else if(tempC>0&&tempC<=45){
  blueTemp= map(tempC, 0, 45, 255, 0);
 }
else if(tempC>45){
  blueTemp = 0;
 }

if(tempC<15){
  greenTemp = 0;
}
else if(tempC>15&&tempC<=35){
  greenTemp = map(tempC, 15, 35, 1, 254);
}
else if(tempC>35&&tempC<=85){
  greenTemp = map(tempC, 35, 85, 255, 0);
}
else if(tempC>85){
  greenTemp = 0;
}

if(tempC<65){
  redTemp = 0;
}
else if(tempC>=65){
  redTemp= map(tempC, 65, 90, 1, 255);
}
else if(tempC>90){
redTemp = 255;
}

colorWipe(strip.Color(redTemp, greenTemp, blueTemp));

delay(2000);                           //wait 200 ms before sending new data
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(20);
  }
}


