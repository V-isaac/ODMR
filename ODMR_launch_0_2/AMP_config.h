// Config file for ADA2200
// Contains all the comands and possible constants for ADA2200
const byte am_serial	 = 0x00; 			 // serial interface
const byte am_reset		 = 0b10000001; // resets the interface
																		 
const byte an_pin_conf = 0x28; 			 // remember to send 0x00 before it
const byte an_pin1		 = 0b00000011; // only INP, device uses CLKIN

const byte demod			 = 0x2A;
const byte demod1			 = 0b00011001; // no phase, mixer ON, SDO to pin 13, VOCM is in fast settling mode

const byte clkin_conf	 = 0x2B;
const byte clkin1			 = 0x00000001; // Fclkin = Fsi, Fm = Fsi / 8
