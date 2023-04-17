#include <HX711.h>

#define LOADCELL_DOUT_PIN 32
#define LOADCELL_SCK_PIN 33

HX711 scale;


void setup() {
  Serial.begin(115200);
  delay(10);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); 
  Serial.println("Start");
}

void loop() {

  float pressure_sum = 0;
  int p_sum = 0;
  float pressure_start;
  //Serial.print("Raw value: ");
  //Serial.println(scale.read());
  int pressure = (scale.read_average(25));
  //pressure_start = (scale.read_average(25));
  //pressure = pressure - 2450000;     // add offset
  //pressure = pressure * (-0.000018); // add scale factor

  for(int i=0; i<=9; i++)
  {
    //float pressure = (scale.read_average(5));
    //pressure_sum = 
    //p_sum = p_sum + ( ( scale.read_average(10) * (0.0003815) ) / 2 );
  }
  //int pressure_s = p_sum / 10;
  
  //float pressure_r = pressure * (0.001);
  int pressure_s = ( pressure * (0.0003815) );
  int p_percent = map(pressure_s, 0, 450, 0, 100);
  //int pressure_s = pressure * (0.000003815);
  Serial.print("Level%:");
  //Serial.println(pressure,HEX);
  //Serial.println(pressure_s);

  Serial.print(p_percent);
  
  Serial.print("  Pressure:");
  Serial.println(pressure_s);
  
  delay(50);

}
