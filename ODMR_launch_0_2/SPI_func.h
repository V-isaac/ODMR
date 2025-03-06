
float SPI_read(SPIClass* spi, byte msg0, byte msg1, byte msg2, byte msg3){
	digitalWrite(spi -> pinSS(), LOW);
	spi -> transfer(msg0);
	byte out1 = spi -> transfer(msg1);
	byte out2 = spi -> transfer(msg2);
	byte out3 = spi -> transfer(msg3);
	digitalWrite(spi -> pinSS(), HIGH);

	float var = 0;
	var = (out1 << 16) | (out2 << 8)| out3;
	return var;
}


void SPI_write(SPIClass* spi, byte msg0, byte msg1, byte msg2, byte msg3){
	digitalWrite(spi -> pinSS(), LOW);
	spi -> transfer(msg0);
	spi -> transfer(msg1);
	spi -> transfer(msg2);
	spi -> transfer(msg3);
	digitalWrite(spi -> pinSS(), HIGH);
	delay(1);
}

void SPI_write(SPIClass* spi, byte msg0, byte msg1, byte msg2){
	digitalWrite(spi -> pinSS(), LOW);
	spi -> transfer(msg0);
	spi -> transfer(msg1);
	spi -> transfer(msg2);
	digitalWrite(spi -> pinSS(), HIGH);
	delay(1);
}

void SPI_write(SPIClass* spi, byte msg0, byte msg1){
	digitalWrite(spi -> pinSS(), LOW);
	spi -> transfer(msg0);
	spi -> transfer(msg1);
	delay(1);
	digitalWrite(spi -> pinSS(), HIGH);
}
