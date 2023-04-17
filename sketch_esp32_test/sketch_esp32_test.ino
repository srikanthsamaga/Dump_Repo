/*

*/

#define LED_BUILTIN 2 // define the GPIO 2 as LED_BUILTIN
#define ESP32_BUTTON 0

uint8_t button_laststate;
uint8_t button_state;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); // initialize GPIO pin 2 LED_BUILTIN as an output.
  pinMode(ESP32_BUTTON, INPUT); // Button input
  
  button_laststate = HIGH;
  
}

void loop() {
  
  button_state = digitalRead(ESP32_BUTTON);
    
  if(button_state != button_laststate){
    if (LOW == button_state)
    {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
      delay (500);
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
      delay(1000);
    }
    button_laststate = button_state;
  }
  
  
}
