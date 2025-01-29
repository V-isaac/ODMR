// Config file for all the defenitions 
// and default values

// PWM as modulating signal
#define PWM_CHANNEL 0    // 0 - 16
#define PWM_FREQ 680     // up to 50k
#define PWM_RESOLUTION 8 // 8 -16

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
#define MAX_DUTY_CYCLE (int)(pow(2, PWM_RESOLUTION) - 1)
#define LED_OUTPUT_PIN 18

// --------------------------------------------- //

// SPI definitions
// AD7192
#define VSPI_MISO 14 			 // RDY pin Srial Data Out. LOW when data is ready to be read
#define VSPI_MOSI 12			 // DIN pin to the Input Shift Register
#define VSPI_SCLK 23			 // Serial Clock
#define VSPI_SS   22			 // Chip Select
#define ADCORDER	MSBFIRST // What it says
													 
// ADA2200
#define HSPI_MISO 26			 //	Doesn't seem to go into ESP32
#define HSPI_MOSI 27			 // SDIO/SDA - bidirectional in/out
#define HSPI_SCLK 21			 // Serial Clock
#define HSPI_SS   25			 // invCS
#define FILORDER	MSBFIST	 // What it says

#if !defined(CONFIG_IDF_TARGET_ESP32)
#define VSPI FSPI
#endif

// Example messages
// #define CONTINIOUS_READ  0b01011100
// #define ONE_TIME_READ    0b01011000 //send while RDY pin is low


// #define BINARY 0b01010101

// --------------------------------------------- //
