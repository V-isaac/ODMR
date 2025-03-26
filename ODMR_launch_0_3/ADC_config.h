// const byte reg_com 	 = 0b00000000; // first byte 
byte reg_stat	 = 0b00000000; // read only 8	== s
byte reg_mod	 = 0b00001000; // 				 24 == m 
byte reg_conf	 = 0b00010000; // 				 24 == c
byte reg_data	 = 0b00011000; //				24/32	== d
byte reg_ID		 = 0b00100000; // read only 8	== i
byte reg_GP		 = 0b00101000; // 				  8	== g
byte reg_set	 = 0b00110000; // 				 24 == o
byte reg_full	 = 0b00111000; // already implemented in loop - use read

// first-time setup
byte conf1 		 = 0b00000000; 
byte conf2		 = 0b00000000; 
byte conf3		 = 0b00000000; 

byte cont_conv = 0b00001000; 
byte mode2		 = 0b00000000; 
byte mode3 		 = 0b01100000; 	// 000, 011, 100, 101, 110, 111
byte gain = 1; 								// 1,		8,	 16,	32,	 64,	128

// variables related to ADC
byte out1, out2, out3, pin;
byte in1, in2, in3;

String no_write = "You cannot write to this register";

float avr;
float a_temp[it];
float var;
uint32_t cread;
