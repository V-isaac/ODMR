// ADC config
// Contains all the comands and possible constants regarding AD7192
//										 0b0wREG000
const byte read_data = 0b01011000; // one time read
const byte read_cont = 0b01011100; // continious read

const byte con_reg   = 0b00010000; // write data to configuration register - 24 bits
const byte conf1 		 = 0b00000000; // chop disabled - CR16 - CR23
const byte conf2		 = 0b00000000; // CR15 - CR8 channel select bits
const byte conf3		 = 0b00000000; // CR7  - CR0 gain == 1 (+-5V)
										//       UGai

const byte mode_reg  = 0b00001000; // write data to mode register - 24 bits
const byte mode1 		 = 0b00001000; // MR16 - MR24
const byte mode2		 = 0b00000000; // MR8  - MR15
const byte mode3 		 = 0b00000000; // MR0  - MR7	FS == 500 


byte out1, out2, out3, pin;
int32_t var;
