#include <SPI.h>

#include "ODMR_config.h"
#include "ADC_config.h"

// PWM setup
int freq;
uint8_t binary, b_temp, b_in;
byte temp; // 8 bits for temp

static const int spiClk = 10000;  // 10 kHz spiClock - bare minimum for AD7192
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
  // pins of our choice
  vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  //23, MISO, MOSI, SS
  
  #ifndef ALTERNATE_PINS
    // default SCLK = 14, MISO = 12, MOSI = 13, SS = 15
    hspi->begin();
  #else
    // pins of our choice
    hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);  //SCLK, MISO, MOSI, SS
  #endif

  // Setting up Chip Select pins as Arduino IDE doesn't do that by default
  pinMode(vspi->pinSS(), OUTPUT);  //VSPI SS
  pinMode(hspi->pinSS(), OUTPUT);  //HSPI SS
	
	// configuring ADC
	vspi -> beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(mode_reg);
	WAIT();
	vspi -> transfer(mode1);
	WAIT();
	vspi -> transfer(mode2);
	WAIT();
	vspi -> transfer(mode3);
	WAIT();

	vspi -> transfer(comm_reg);
	WAIT();
	vspi -> transfer(conf1);
	WAIT();
	vspi -> transfer(conf2);
	WAIT();
	vspi -> transfer(conf3); 
	WAIT();
	digitalWrite(VSPI_MOSI, HIGH);
	digitalWrite(vspi -> pinSS(), HIGH);
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> endTransaction();

	attachInterrupt(digitalPinToInterrupt(VSPI_MISO), ADCread, FALLING);
}

void loop() {

  // Re-setup PWM on current channel with said frequency
  // ledcSetup(PWM_CHANNEL, freq, PWM_RESOLUTION);
  // ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE/2);
  // mPrint(Serial, "LEDC reconfigured to ", freq, "\n\r");
}

inline void WAIT(){
	delay(5);
}

// execute on interrupt - we have data to read
void ADCread(){
		vspi -> beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
		digitalWrite(vspi -> pinSS(), LOW);  
		vspi -> transfer(send_data);
		out1 = vspi -> transfer(0xff);
		out2 = vspi -> transfer(0xff);
		out3 = vspi -> transfer(0xff);
		digitalWrite(vspi -> pinSS(), HIGH); 
		vspi -> endTransaction();

		mPrint(Serial, "\n\r", out1, "\t", out2, "\t", out3, "\n\r");
}
