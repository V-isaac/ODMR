const byte read_cont = 0b01011100; 

const byte con_reg   = 0b00010000; 
const byte conf1 		 = 0b00000000; 
const byte conf2		 = 0b00000000; 
const byte conf3		 = 0b00000000; 

const byte mode_reg  = 0b00001000; 
const byte cont_conv = 0b00001000; 
const byte mode2		 = 0b00000000; 
const byte mode3 		 = 0b01100000;

const byte gain = 1;

byte out1, out2, out3, pin;
float avr;
float a_temp[it];
float var;
uint32_t cread;
