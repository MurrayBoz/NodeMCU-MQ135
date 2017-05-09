/****************************************************************
 Display Screens (overview --> air --> water --> status --> Reminder if applicable) 
****************************************************************/
void displayOLED() {
  String message = "[displayOLED] ";
  Serial.println(message);
  
  display.clearDisplay(); // Make sure the display is cleared
  display.setCursor(0,0);
  message = "Temperature: ";
  message += airTemperature;
  display.println(message);
  message = "Humidity: ";
  message += airHumidity;
  display.println(message);
  display.println();
  message = "RZero (get): ";
  message += rzero;
  display.println(message);
  message = "RZero (lib): ";
  message += RZERO;
  display.println(message);
  display.println();
  message = "PPM: ";
  message += ppm;
  display.println(message);
  message = "PPM (A): ";
  message += ppmbalanced;
  display.println(message);
  display.display();
  
}

/****************************************************************
 Init OLED screen 
****************************************************************/
void initOLED () {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize OLED display
  display.clearDisplay();                     // Make sure the display is cleared
  display.setTextSize(1);                     // 21 characters per line
  display.setTextColor(WHITE);
  display.drawBitmap(0, 0, UrbanPotagerLogo1, 128, 64, WHITE);// Draw U Logo 
  display.display();
  delay(2000);
}

