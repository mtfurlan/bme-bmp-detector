
#include <U8g2lib.h>
#include <stdint.h>
#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 5, /* data=*/ 4);
BME280 mySensor;
char buf[512];

void setup()
{
  //***Driver settings********************************//
  //commInterface can be I2C_MODE or SPI_MODE
  //specify chipSelectPin using arduino pin names
  //specify I2C address.  Can be 0x77(default) or 0x76

  //For I2C, enable the following and disable the SPI section
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76;

  //For SPI enable the following and dissable the I2C section
  //mySensor.settings.commInterface = SPI_MODE;
  //mySensor.settings.chipSelectPin = 10;


  //***Operation settings*****************************//

  //renMode can be:
  //  0, Sleep mode
  //  1 or 2, Forced mode
  //  3, Normal mode
  mySensor.settings.runMode = 3; //Normal mode

  //tStandby can be:
  //  0, 0.5ms
  //  1, 62.5ms
  //  2, 125ms
  //  3, 250ms
  //  4, 500ms
  //  5, 1000ms
  //  6, 10ms
  //  7, 20ms
  mySensor.settings.tStandby = 0;

  //filter can be off or number of FIR coefficients to use:
  //  0, filter off
  //  1, coefficients = 2
  //  2, coefficients = 4
  //  3, coefficients = 8
  //  4, coefficients = 16
  mySensor.settings.filter = 0;

  //tempOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.tempOverSample = 1;

  //pressOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
    mySensor.settings.pressOverSample = 1;

  //humidOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.humidOverSample = 1;

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

  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  mySensor.begin();
}

void loop() {
  Serial.print("register 0xD0: 0x");
  int sensorType = mySensor.readRegister(0xD0);
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
