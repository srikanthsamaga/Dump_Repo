//
//    FILE: HX_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711


#include "HX711.h"

HX711 scale;

uint8_t dataPin = 16;
uint8_t clockPin = 0;

uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  // Serial.println(__FILE__);
  // Serial.print("LIBRARY VERSION: ");
  // Serial.println(HX711_LIB_VERSION);
  // Serial.println();

  scale.begin(dataPin, clockPin);

  // TODO find a nice solution for this calibration..
  // load cell factor 20 KG
  // scale.set_scale(127.15);
  // load cell factor 5 KG
  scale.set_scale(420.0983);       // TODO you need to calibrate this yourself.
  // reset the scale to zero = 0
  scale.tare();
}


void loop()
{
  // continuous scale 4x per second
  //f = scale.get_units(5);
  //Serial.println(f);
  //delay(250);

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


// -- END OF FILE --
