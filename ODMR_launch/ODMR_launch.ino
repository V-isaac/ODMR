#include <SPI.h>

#include "ODMR_config.h"
#include "ADC_config.h"
#include "AMP_config.h"

// PWM setup
int freq;
int temp;
// for messages: 0xFF == 0b11111111

/*
Chip		min	max units
ADA2200			20 	MHz
AD7192	10  10k	kHz
*/
static const int spiClk = 200000;
//static const int spiClk = 49000000; 

//uninitialized pointers to SPI objects
SPIClass *vspi = NULL;
// SPIClass *hspi = NULL;

void setup() {
  Serial.begin(115200);
  Serial.print("entered setup \n\r");

  // ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  // ledcAttachPin(CLKIN, PWM_CHANNEL);
  // ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE/2);

  // initialising SPI protocols, using only 2 available on ESP32
  vspi = new SPIClass(VSPI);
  // hspi = new SPIClass(HSPI);

  // Defining SPIs pins
  vspi -> begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  //SC  MISO, MOSI, SS
	// hspi -> begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);  //SCLK, MISO, MOSI, SS
	
	// Explicitly setting pins as output/input
  pinMode(vspi->pinSS(), OUTPUT);  
	// Ensure CS is high at initialisation
	digitalWrite(vspi -> pinSS(), HIGH);
	// digitalWrite(hspi -> pinSS(), HIGH);
  ADCresert();

  vspi -> beginTransaction(SPISettings(spiClk, ADCORDER, ADC_MODE));
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(con_reg);
  vspi -> transfer(conf1);
  vspi -> transfer(conf2);
  vspi -> transfer(conf3);
  digitalWrite(vspi -> pinSS(), HIGH);
  vspi -> endTransaction();
	delay(1);

	vspi -> beginTransaction(SPISettings(spiClk, ADCORDER, ADC_MODE));
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(mode_reg);
  vspi -> transfer(mode1);
  vspi -> transfer(mode2);
  vspi -> transfer(mode3);
  digitalWrite(vspi -> pinSS(), HIGH);
  vspi -> endTransaction();
	delay(1);
	
	// setting up continious read
	vspi -> beginTransaction(SPISettings(spiClk, ADCORDER, ADC_MODE));
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(read_cont); 

	// attachInterrupt(digitalPinToInterrupt(VSPI_MISO), ADCread, FALLING); // execute function on falling edge of MISO
  mPrint(Serial, "Done setting up \n\r"); 
}

void loop() {
  while(digitalRead(VSPI_MISO) != LOW){}
  /* while (1){
   if (Serial.available()){ temp = Serial.read(); break;} 
  } */
  out1 = vspi -> transfer(0x00);
	out2 = vspi -> transfer(0x00);
	out3 = vspi -> transfer(0x00);
		//digitalWrite(vspi -> pinSS(), HIGH); 
		//vspi -> endTransaction();

  var = 0;
  var = out1;
  var = var << 8 + out2; 
  var = var << 8 + out3; 
	mPrint(Serial, var, "\n\r");
}


void ADCresert(){
	vspi -> beginTransaction(SPISettings(spiClk, ADCORDER, ADC_MODE)); //  is high when inactive, sample on falling edge
	digitalWrite(vspi -> pinSS(), LOW);
	vspi -> transfer(0xFF); // 8 bits each
	vspi -> transfer(0xFF); // 16
	vspi -> transfer(0xFF); // 24
	vspi -> transfer(0xFF); // 32
	vspi -> transfer(0xFF); // 40
	digitalWrite(vspi -> pinSS(), HIGH);
	vspi -> endTransaction();

	delay(1);
}
// execute on interrupt - we have data to read
void ADCread(){
		//vspi -> beginTransaction(SPISettings(spiClk, ADCORDER, ADC_MODE));
		//digitalWrite(vspi -> pinSS(), LOW);  
		//vspi -> transfer(send_data);
		
}
