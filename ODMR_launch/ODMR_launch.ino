#include "ODMR_config.h"
#include <SPI.h>

// PWM setup
int freq, temp;

static const int spiClk = 1000000;  // 1 MHz spiClock
//uninitialized pointers to SPI objects
SPIClass *vspi = NULL;
SPIClass *hspi = NULL;

void setup() {
  Serial.begin(115200);

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE/2);

  // Using only 2 available SPIs
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);
  // Defining SPIs pins
  #ifndef ALTERNATE_PINS
    // default SCLK = 18, MISO = 19, MOSI = 23, SS = 5
    vspi->begin();
  #else
    // pins of our choice
    vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  //SCLK, MISO, MOSI, SS
  #endif
  #ifndef ALTERNATE_PINS
    // default SCLK = 14, MISO = 12, MOSI = 13, SS = 15
    hspi->begin();
  #else
    // pins of our choice
    hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);  //SCLK, MISO, MOSI, SS
  #endif

  // Setting up Chip Select pins as Arduino doesn't do that by default
  pinMode(vspi->pinSS(), OUTPUT);  //VSPI SS
  pinMode(hspi->pinSS(), OUTPUT);  //HSPI SS

  // spiCommand(vspi, BINARY);
}

void loop() {
  while (1){
    // if there's something to read
    if (Serial.available()) {
      // parse it
      temp = Serial.parseInt();
      // check validity
      if (temp > 0) freq = temp;
      // set as our frequency and break out of loop
      break;
    }
  }

  // Re-setup PWM on current channel with said frequency
  ledcSetup(PWM_CHANNEL, freq, PWM_RESOLUTION);
  ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE/2);
  mPrint(Serial, "LEDC reconfigured to ", freq, "\n\r");
}