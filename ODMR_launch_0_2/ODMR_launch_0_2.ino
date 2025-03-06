#include <SPI.h>
#include "SPI_func.h" 		// Abstraction over SPI objects

#include "ODMR_config.h" 	// Pin config and constants
#include "ADC_config.h"		// ADC constants
#include "AMP_config.h"		// AMP constants


SPIClass *vspi = NULL;
SPIClass *hspi = NULL;

void setup() {
  Serial.begin(115200);

	// Setting up modulating signal
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION); 
  ledcAttachPin(CLKIN, PWM_CHANNEL);								
  ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE/2);					

	// Setting up SPI protocols
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);

  vspi -> begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  
	hspi -> begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);  

	vspi -> setBitOrder(ADC_ORDER);
	vspi -> setDataMode(ADC_MODE);
	vspi -> setFrequency(spiClk);

	hspi -> setBitOrder(AMP_ORDER);
	hspi -> setDataMode(AMP_MODE);
	hspi -> setFrequency(spiClk);
	
  pinMode(vspi -> pinSS(), OUTPUT);  
  pinMode(hspi -> pinSS(), OUTPUT);  

	digitalWrite(vspi -> pinSS(), HIGH);
	digitalWrite(hspi -> pinSS(), HIGH);

	// Setting up registers on AMP and ADC
	AMPreset();
	SPI_write(hspi, 0x00, an_pin_conf, an_pin1);
	SPI_write(hspi, 0x00, demod, demod1);
	SPI_write(hspi, 0x00, clkin_conf, clkin1);
	
  ADCresert();
	SPI_write(vspi, con_reg, conf1, conf2, conf3);
	SPI_write(vspi, mode_reg, cont_conv, mode2, mode3);

  mPrint(Serial, "minimum \t maximum \t current value \n\r");
}


void loop() {
	delay(10/it);

	if (digitalRead(VSPI_MISO) == LOW){
		var = 0;
		var = SPI_read(vspi, read_cont, 0xff, 0xff, 0xff);
		
		temp = 3.3 * (var / (1 << 23) - 1);
		a_temp[i] = temp;
		i++;

		if (i == (it - 1)) [[unlikely]] {
		 	for (int j = 0; j < (it -1); j++){
		 		temp += a_temp[j];
		 	}
		 	temp = temp/it;
		 	i = 0;
      if (temp < minimum) minimum = temp -1;
      if (temp > maximum) maximum = temp +1;
      mPrint(Serial, minimum, "\t", maximum, "\t"); 
			Serial.println(temp); 
		 }
	}
}


void ADCresert(){
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(0xff);
	vspi -> transfer(0xff);
	vspi -> transfer(0xff);
	vspi -> transfer(0xff);
	vspi -> transfer(0xff);
	digitalWrite(vspi -> pinSS(), HIGH);
}

void AMPreset(){
	SPI_write(hspi, 0x00, am_serial, am_reset);
	SPI_write(hspi, 0x00, am_serial, 0x00);
}


