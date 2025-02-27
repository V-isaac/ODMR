// ADC config
// Contains all the comands and possible constants regarding AD7192
//										 0b0wREG000
const byte read_data = 0b01011000; // one time read
const byte read_cont = 0b01011100; // continious read

const byte con_reg   = 0b00010000; // write data to configuration register - 24 bits
const byte conf1 		 = 0b00000000; // chop disabled - CR16 - CR23
const byte conf2		 = 0b00000000; // CR15 - CR8 channel select bits
const byte conf3		 = 0b00010000; // CR7  - CR0 gain == 1 (+-5V)
										//      BUGai

const byte mode_reg  = 0b00001000; // write data to mode register - 24 bits
									  //   ModCl
const byte cont_conv = 0b00001000; // default
const byte one_read  = 0b00101000; // first byte, single conversion	

const byte mode2		 = 0b00000000; // default
const byte mode3 		 = 0b01100000; //	FS == 1200 

byte out1, out2, out3, pin;
int32_t var;

// conversion definitions
// uncomment at least one for it to compile
// #define SINGLE_CONVERSION			 // currently broken, but kinda works?
#define CONTINUOUS_CONVERSION
// #define CONTINUOUS_READ
