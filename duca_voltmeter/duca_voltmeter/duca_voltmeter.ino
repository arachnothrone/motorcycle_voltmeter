

#include <Wire.h> 
#include <U8x8lib.h>

#define CORRECTION_COEFF  1.076

int analogInput = A0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0;  // R1 = 100K  - input V+
float R2 = 10000.0;   // R2 = 10K   - input V-
int value = 0;

U8X8_SSD1306_128X32_UNIVISION_HW_I2C oled(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C


// void clockDisplayFunc(TimeDateStorage* tds)
// {
//   /* Display clock values on the screen */
  
//   printRtcValueOnDisplay(0, 0, tds->hrs);

//   printRtcValueOnDisplay(3, 0, tds->min);

//   printRtcValueOnDisplay(6, 0, tds->day);
//   oled.print("-");

//   printRtcValueOnDisplay(9, 0, tds->mnth);
//   oled.print("-");

//   oled.setCursor(12, 0);
//   oled.print(tds->year);
// }

void printValueOnDisplay(uint8_t xPos, uint8_t yPos, uint8_t value)
{
  oled.setCursor(0, yPos);
  oled.print("              $");
  oled.setCursor(xPos, yPos);
  oled.print(value);
}

void printVoltageOnDisplay(uint8_t xPos, uint8_t yPos, float value)
{
  oled.setCursor(0, yPos);
  oled.print("         ");
  oled.setCursor(xPos, yPos);
  
  oled.print(value);
  oled.print("v");
}


void setup() {
  pinMode(/*A0*/analogInput, INPUT);                       // Analog input: Voltage 0 - 90V

  Wire.begin();

  // Set up OLED display
  oled.begin();
  oled.setPowerSave(0);
  oled.setFont(u8x8_font_px437wyse700a_2x2_r); // u8x8_font_chroma48medium8_r u8x8_font_px437wyse700a_2x2_r u8g2_font_courB12_tf 
  oled.setContrast(11);

}

void loop() {
  value = analogRead(/*A0*/analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = CORRECTION_COEFF * vout / (R2 / (R1 + R2));
  if (vin < 0.01)
  {
    vin = 0.0;
  }
  printVoltageOnDisplay(3, 0, vin);
  //printValueOnDisplay(5, 3, value);
  delay(2000);
}
