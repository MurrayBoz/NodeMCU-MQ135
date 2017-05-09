/****************************************************************
 Initialization of the NeoPixel Ring (smooth animation)
****************************************************************/
void initNeoPixelRing() {
  int r, g, b;
  strip.begin();                              // Setup NeoPixel Ring
  strip.setBrightness(NEOPIXEL_BRIGHT);        // Adjust brightness here
  for(int i=0; i<24; i++) { 
    strip.setPixelColor(sine[i], strip.Color(0, 0, 0)); //change RGB color value here
  }
  strip.show(); // Initialize all pixels to 'off'
  for(int i=0; i<25; i++) {                   // NeopPixel Animation 

    r=0;    // GREEN
    g=255;
    b=0;
    
    strip.setPixelColor(sine[i], strip.Color(r, g, b)); //change RGB color value here
    delay(40);
    strip.show(); 
  } 
}



/****************************************************************
 Refresh NeoPixel Water Level display
****************************************************************/
void refreshNeoPixelRing() { 
  int r;
  int g;
  int b;
  if (ppmbalanced <=5000) {
    r=255;  // ORANGE
    g=165;
    b=0;  
    PPMStatus =2;
  }
  if (ppmbalanced <=1100) {
    r=0;    // GREEN
    g=255;
    b=0;
    PPMStatus =1;
  }
  
  if (ppmbalanced >5000) {
    r=255;  // RED
    g=0;
    b=0;
    PPMStatus =3;
  }

  //if (PPMStatus != PPMStatusOld) {
    PPMStatusOld = PPMStatus;
    for(int i=0; i<24; i++) { 
      strip.setPixelColor(sine[i], strip.Color(0, 0, 0)); //change RGB color value here
    }
    strip.show(); 
  
    for(int i=0; i<24; i++) { 
      strip.setPixelColor(sine[i], strip.Color(r, g, b)); //change RGB color value here
      delay(20);
      strip.show();   
    }   
  //}
}
