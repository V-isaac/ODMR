#include <SPI.h>

#include "ODMR_config.h"
#include "ADC_config.h"
#include "AMP_config.h"

// PWM setup
// int freq;
// int temp;
// for messages: 0xFF == 0b11111111

/*
Chip		min	max units
ADA2200			20 	MHz
AD7192	10  		kHz
*/
static const int spiClk = 1000000;

//uninitialized pointers to SPI objects
SPIClass *vspi = NULL;
SPIClass *hspi = NULL;

void setup() {
  Serial.begin(115200);
  Serial.print("entered setup \n\r");
	
	// Setup modulating signal
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION); // PWM generator, freq, resolution
  ledcAttachPin(CLKIN, PWM_CHANNEL);								// pin, PWM generator
  ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE/2);					// generate PWM with said duty

  // initialising SPI protocols, using only 2 available on ESP32
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);

  // Defining SPIs pins
  vspi -> begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  //SC  MISO, MOSI, SS
	hspi -> begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);  //SCLK, MISO, MOSI, SS

	vspi -> setBitOrder(ADC_ORDER);
	vspi -> setDataMode(ADC_MODE);
	vspi -> setFrequency(spiClk);

	hspi -> setBitOrder(AMP_ORDER);
	hspi -> setDataMode(AMP_MODE);
	hspi -> setFrequency(spiClk);
	
	// Explicitly setting pins as output/input
  pinMode(vspi -> pinSS(), OUTPUT);  
  pinMode(hspi -> pinSS(), OUTPUT);  
	// Ensure CS is high at initialisation
	digitalWrite(vspi -> pinSS(), HIGH);
	digitalWrite(hspi -> pinSS(), HIGH);

	digitalWrite(hspi -> pinSS(), LOW);
	hspi -> transfer(0x00);
	hspi -> transfer(an_pin_conf);
	hspi -> transfer(an_pin1);
  digitalWrite(hspi -> pinSS(), HIGH);

	digitalWrite(hspi -> pinSS(), LOW);
	hspi -> transfer(0x00);
	hspi -> transfer(demod);
	hspi -> transfer(demod1);
  digitalWrite(hspi -> pinSS(), HIGH);

	digitalWrite(hspi -> pinSS(), LOW);
	hspi -> transfer(0x00);
	hspi -> transfer(clkin_conf);
	hspi -> transfer(clkin1);
  digitalWrite(hspi -> pinSS(), HIGH);

  ADCresert();

	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(con_reg);
  vspi -> transfer(conf1);
  vspi -> transfer(conf2);
  vspi -> transfer(conf3);
  digitalWrite(vspi -> pinSS(), HIGH);
	delay(1);

	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(mode_reg);
  vspi -> transfer(mode1);
  vspi -> transfer(mode2);
  vspi -> transfer(mode3);
  digitalWrite(vspi -> pinSS(), HIGH);
	delay(1);
	
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(read_cont); 

  mPrint(Serial, "Done setting up \n\r"); 
}

void loop() {
	if (digitalRead(VSPI_MISO) == LOW){
		out1 = vspi -> transfer(0x00);
		out2 = vspi -> transfer(0x00);
		out3 = vspi -> transfer(0x00);

		var = 0;
		var = (out1 << 16) | (out2 << 8) | out3;
		Serial.println(var, BIN);
	}
}


void ADCresert(){
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(0xFF); // 8 bits each
	vspi -> transfer(0xFF); // 16
	vspi -> transfer(0xFF); // 24
	vspi -> transfer(0xFF); // 32
	vspi -> transfer(0xFF); // 40
	vspi -> transfer(0xFF); // 48
	digitalWrite(vspi -> pinSS(), HIGH);
	delay(1);
}

/*
// execute on interrupt - we have data to read
void ADCread(){
		//vspi -> beginTransaction(SPISettings(spiClk, ADCORDER, ADC_MODE));
		//digitalWrite(vspi -> pinSS(), LOW);  
		//vspi -> transfer(send_data);
		
} */
