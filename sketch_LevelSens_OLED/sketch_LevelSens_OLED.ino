#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
   
   Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  //display.display();
  //delay(1000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(F("Template"));
  display.display();      // Show initial text
  delay(1000);
  // Clear the buffer
  display.clearDisplay();
  display.display();

  //display.setCursor(0, 10);
  //display.println("Pressure");
  //display.drawRoundRect(0, 12, display.width()-2, 5, 2, WHITE);
  //fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
  Serial.println(display.height());
 
  //display.fillRoundRect(0, 12, 30, 5, 2, WHITE);
  //display.display();
  delay(1000);
}

void loop() {

   for (int16_t i=1;i<=display.height()-2; i=i+5){
    display.fillRoundRect(0, i , (i*2), 4, 2, WHITE);
    //delay(2000);
    Serial.println(i);
    display.display();
    delay(1000);
  }

  display.clearDisplay();
  display.display();

}
