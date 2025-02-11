// Config file for ADA2200
// Contains all the comands and possible constants for ADA2200

const byte an_pin_conf = 0x28 // remember to send 0x00 before it
const byte ab_pin1		 = 0x03	// only INP, device uses CLKIN

const byte demod			 = 0x2A
const byte demod1			 = 0b00010010 // no phase, mixer ON, SDO to pin 13, VOCM is in fast settling mode

const byte clkin_conf	 = 0x2B
const byte clkin1			 = 0x03
