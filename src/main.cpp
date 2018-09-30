
#include <U8g2lib.h>
#include <stdint.h>
#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 5, /* data=*/ 4);
BME280 bmeSensor;
char buf[512];

void setup()
{
  bmeSensor.settings.commInterface = I2C_MODE;
  bmeSensor.settings.I2CAddress = 0x76;
  bmeSensor.settings.runMode = 3; //Normal mode

  Serial.begin(115200);
  Serial.print("Program Started\n");

  // --- Display ---
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14_mf);
  u8g2.drawStr(0,10, "BME/BMP Detector");
  u8g2.drawStr(30,30, "v0.42");
  u8g2.sendBuffer();
  delay(2000);

}

void loop() {
  delay(5);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up claims sparkfun
  bmeSensor.begin();
  Serial.print("register 0xD0: 0x");
  int sensorType = bmeSensor.readRegister(0xD0);
  Serial.println(sensorType, HEX);

  u8g2.clearBuffer();
  sprintf(buf, "register: 0x%02X", sensorType);
  u8g2.drawStr(0,10, buf);
  switch(sensorType) {
    case 0x00:
      sprintf(buf, "sensor: NONE");
      break;
    case 0x58:
      sprintf(buf, "sensor: BMP");
      break;
    case 0x60:
      sprintf(buf, "temp: %f", bmeSensor.readTempC());
      u8g2.drawStr(0,50, buf);

      sprintf(buf, "sensor: BME");
      break;
    default:
      sprintf(buf, "sensor: UNKNOWN");
      break;
  }

  u8g2.drawStr(0,30, buf);
  u8g2.sendBuffer();
  delay(100);
}
