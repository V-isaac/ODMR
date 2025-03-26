#include "ODMR_config.h" 	// Pin config and constants
#include "ADC_config.h"		// ADC constants
#include "AMP_config.h"		// AMP constants

#include <SPI.h>
#include "SPI_func.h" 		// Abstraction over SPI objects


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
	SPI_write(vspi, reg_conf, conf1, conf2, conf3);
	SPI_write(vspi, reg_mod, cont_conv, mode2, mode3);

  Serial.print( "minimum \t maximum \t current value \n\r");
	delay(2000);
}


void loop() {
	delay(10/it);

	if (Serial.available() != 0)[[unlikely]]{
		serial_com = Serial.read();
		switch (serial_com){
			case 's':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_stat, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					Print(Serial, no_write, "\r\n");
				}
				delay(5000);
				break;

			case 'm':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_mod, 0x00, 0x00, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					spi_val = SerialRead(24); // how many bytes to read
					Serial.println(spi_val, BIN);
					in1 = spi_val >> 16;
					in2 = spi_val >> 8;
					in3 = spi_val;
					Serial.println(in1, BIN);
					Serial.println(in2, BIN);
					Serial.println(in3, BIN);
					SPI_write(vspi, reg_mod, in1, in2, in3);
				}
				
				break;

			case 'c':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_conf, 0x00, 0x00, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					spi_val = SerialRead(24);
					in1 = spi_val >> 16;
					in2 = spi_val >> 8;
					in3 = spi_val;
					SPI_write(vspi, reg_conf, in1, in2, in3);
				}
				break;

			case 'd':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_data, 0x00, 0x00, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					spi_val = SerialRead(24);
					in1 = spi_val >> 16;
					in2 = spi_val >> 8;
					in3 = spi_val;
					SPI_write(vspi, reg_conf, in1, in2, in3);
				}
				break;

			case 'i':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_ID, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					Print(Serial, no_write, "\r\n");
				}
				break;

			case 'g':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_GP, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					spi_val = SerialRead(8); 
					in1 = spi_val;
					SPI_write(vspi, reg_GP, in1);
				}
				break;
			
			case 'o':	// --------------------
				serial_com = Serial.read();
				if (serial_com == 'r'){
					spi_val = SPI_read(vspi, 0b01000000 | reg_set, 0x00, 0x00, 0x00);
					Serial.println(spi_val, BIN);
					delay(5000);
				}
				if (serial_com == 'w'){
					spi_val = SerialRead(24);
					in1 = spi_val >> 16;
					in2 = spi_val >> 8;
					in3 = spi_val;
					SPI_write(vspi, reg_set, in1, in2, in3);
				}
				break;
		
			case 'r': // full reset
				Serial.print("Are you sure? \r\nIt will fully reset chips \r\n");
				while(Serial.available() == 0){} 
				serial_com = Serial.read();
				if(serial_com == 'r'){

					digitalWrite(vspi -> pinSS(), HIGH);
					digitalWrite(hspi -> pinSS(), HIGH);

					AMPreset();
					SPI_write(hspi, 0x00, an_pin_conf, an_pin1);
					SPI_write(hspi, 0x00, demod, demod1);
					SPI_write(hspi, 0x00, clkin_conf, clkin1);
					
					ADCresert();
					SPI_write(vspi, reg_conf, conf1, conf2, conf3);
					SPI_write(vspi, reg_mod, cont_conv, mode2, mode3);
					Print(Serial, "5 seconds to clear output \r\n");
					delay(5000);
					Print(Serial, "minimum \t maximum \t current value \r\n");

					break;
				}
				else {
					Serial.print("Did not reset\r\n");
					delay(5000);
					break;
				}
		}
	}	

  /* 
	if (digitalRead(VSPI_MISO) == LOW){
		cread = SPI_cread(vspi, 0b01000000 | reg_full, 0xff, 0xff, 0xff);
		var = cread;
		
		avr= 3.3 / gain * (var/ (1 << 23) - 1);
		a_temp[i] = avr;
		i++;

		if (i == (it - 1)) [[unlikely]] {
		 	for (int j = 0; j < (it -1); j++){
		 		avr+= a_temp[j];
		 	}
		 	avr = avr / it;
		 	i = 0;
      if (avr< minimum) minimum = avr-1;
      if (avr> maximum) maximum = avr+1;
      Print(Serial, minimum, "\t", maximum, "\t", avr, "\n\r"); 
		 }
	}
	*/
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


