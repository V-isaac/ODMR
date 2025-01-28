// ADC config
// Contains all the comands and possible constants regarding AD7192

const byte send_data = 0b01011000; // read data from data register 24/32 bits

const byte mode_reg  = 0b00001000; // write data to mode register - 24 bits
const byte mode1 		 = 0b00001000; // MR16 - MR24
const byte mode2		 = 0b00000000; // MR8  - MR15
const byte mode3 		 = 0b01100000; // MR0  - MR7	FS == 500 

const byte comm_reg  = 0b00010000; // write data to configuration register - 24 bits
const byte conf1 		 = 0b00000000; // chop enabled - CR16 - CR24
const byte conf2		 = 0b00000001; // CR15 - CR8 channel select bits
const byte conf3		 = 0b00001001; // CR7  - CR0 gain == 1 (+-5V), unipolar

byte out1, out2, out3, pin;
unsigned long var;
/*
	could be sent to loop(){} to combine data into one variable via 8 bit shift

	var = 0b0000000;
	var = var * 256 + out1;
	var = var * 256 + out2; 
	var = var * 256 + out3;
*/
