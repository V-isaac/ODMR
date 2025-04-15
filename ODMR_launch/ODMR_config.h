// Config file for all the defenitions 
// and default values

// PWM as modulating signal
#define PWM_CHANNEL 0    // 0 - 16
#define PWM_FREQ 680 * 8 // up to 50k, there's clock divider for modulation, hence multiplication
#define PWM_RESOLUTION 8 // 8 -16

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
#define MAX_DUTY_CYCLE (int)(pow(2, PWM_RESOLUTION) - 1)
#define CLKIN			21			 	// need to look into clock pin

// SPI definitions
// AD7192 the ADC
#define VSPI_MISO 12 			 	// RDY pin Srial Data Out. LOW when data is ready to be read
#define VSPI_MOSI 14			 	// DIN pin to the Input Shift Register
#define VSPI_SCLK 23			 	// Serial Clock
#define VSPI_SS   22			 	// Chip Select
#define ADC_ORDER	MSBFIRST 	// What it says
#define ADC_MODE	SPI_MODE3	// single definition of SPI mode

// ADA2200
#define HSPI_MISO 26			 	//	Doesn't seem to go into ESP32, but still needs to be declared
#define HSPI_MOSI 27			 	// SDIO/SDA - bidirectional in/out
#define HSPI_SCLK 26			 	// Serial Clock
#define HSPI_SS   25			 	// invCS
#define AMP_ORDER	MSBFIRST 	// What it says
#define AMP_MODE	SPI_MODE3	// single definition of spi mode

#if !defined(CONFIG_IDF_TARGET_ESP32)
#define VSPI FSPI
#endif

uint8_t i = 0;
char serial_com = ' ';
uint32_t spi_val = 0;
const uint8_t it = 5;  

float minimum = 30000, maximum = -30000;
static const int spiClk = 1000000;
