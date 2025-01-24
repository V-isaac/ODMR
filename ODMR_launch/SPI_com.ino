
// Command to pass information via SPI
void spiCommand(SPIClass *spi, byte data) {
  //use it as you would the regular arduino SPI API
  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(spi->pinSS(), LOW);  //pull SS slow to prep other end for transfer
  spi->transfer(data);
  digitalWrite(spi->pinSS(), HIGH);  //pull ss high to signify end of data transfer
  spi->endTransaction();
}

// if DIN held high for 40 VSPI_SCLK cycles - AD7192 resets
void AD7192_Reset() {
  digitalWrite(VSPI_MOSI, HIGH);
  for (int i = 0; i < 40; i++){
    digitalWrite(VSPI_SCLK, HIGH);
    delay(1);
    digitalWrite(VSPI_SCLK, LOW);
    // equivalent of 1 cycle //
  }
  digitalWrite(VSPI_MOSI, LOW);
}

// Still looking into way to read the data from pins

// people be telling something like this should work - line 17
// need to look into data reading on AD1792

// something = spiComand(SPIs, byte);
// something |= (uint32_t)spiComand(SPIs, byte) << 8;
