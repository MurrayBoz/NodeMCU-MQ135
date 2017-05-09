#include "MQ135.h"
#define ANALOGPIN A0
#include "DHT.h"
#define DHTPIN      D7            // DHTx sensor = 15 (GPIO)   ex D4
#define DHTTYPE     DHT11         // DHTx type
#define NEOPIXEL    D8            // Spare part 3 pins (D8)
#define NEOPIXEL_BRIGHT     20             // Neopixel brightness

#define TIMER_DHT   5
// OLED & I2C
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define TIMER_OLED   1
#include <SimpleTimer.h>        // https://github.com/jfturcot/SimpleTimer
#include "specialchar.h"   // OLED special characters/images

// NeoPixel Init
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, NEOPIXEL, NEO_GRB + NEO_KHZ800); 
//these are the pixels in order of animation-- 24 pixels in total
int sine[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23}; 
int PPMStatus = 0;
int PPMStatusOld = 0;

//DHT
DHT dht(DHTPIN, DHTTYPE); 
// OLED
#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// SimpleTimer
SimpleTimer timerDHT;
SimpleTimer timerOLED;
float airTemperature, airHumidity, ppm, ppmbalanced, rzero;
int initStep=1;                 // 1 = Connection in progress / 2 = Connection Done 
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initOLED();
  initNeoPixelRing();
  dht.begin();                                // Initialize DHT sensor
  timerDHT.setInterval(TIMER_DHT*1000, getDHTvalues); 
  // 1st SENSOR READING 
  getDHTvalues();
  display.clearDisplay();                     // Make sure the display is cleared
  
}

void loop() {
  String message ="";
  timerDHT.run();
  
  
}




/****************************************************************
 Refresh DHT values (temperature + humidity)
****************************************************************/
void getDHTvalues(){
    String message = "[";
  message += millis()/1000;
  //message += GetFormatedDateTime(Rtc.GetDateTime());
  message+= "s - getDHTvalues] ";
  
  // Reading temperature or humidity takes about 250 milliseconds! 
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor) 
  float h = dht.readHumidity(); 
  // Read temperature as Celsius (the default) 
  float t = dht.readTemperature(); 
  // Read temperature as Fahrenheit (isFahrenheit = true) 
  float f = dht.readTemperature(true); 
  // Check if any reads failed and exit early (to try again). 
  if (isnan(h) || isnan(t) || isnan(f) || t>100.00 || h>100.00) { 
    message +="Failed to read from DHT sensor! (h=";
    message +=h;
    message +=" / t=";
    message +=t;
    message +=")";
    Serial.println(message);
    return;
  } else {
    // Compute heat index in Fahrenheit (the default) 
    //float hif = dht.computeHeatIndex(f, h); 
    // Compute heat index in Celsius (isFahreheit = false) 
    //float hic = dht.computeHeatIndex(t, h, false); 
    message += "Temperature: "; 
    message += int(t); 
    message += "C / "; 
    message += "Humidity: "; 
    message += int(h); 
    message += "%";              // message += " %\t"; --> TAB
    Serial.println(message);  
  }
  
  airTemperature = t;
  airHumidity = h;

  
  rzero = gasSensor.getRZero(); //this to get the rzero value, uncomment this to get ppm value
  Serial.print("RZero=");
  Serial.println(rzero); // this to display the rzero value continuously, uncomment this to get ppm value
   
  ppm = gasSensor.getPPM(); // this to get ppm value, uncomment this to get rzero value
  Serial.print("PPM=");
  Serial.println(ppm); // this to display the ppm value continuously, uncomment this to get rzero value
  
  ppmbalanced = gasSensor.getCorrectedPPM(airTemperature, airHumidity); // this to get ppm value, uncomment this to get rzero value
  Serial.print("PPM Corrected=");
  Serial.println(ppmbalanced); // this to display the ppm value continuously, uncomment this to get rzero value
  
  refreshNeoPixelRing();
  
  displayOLED();
}



