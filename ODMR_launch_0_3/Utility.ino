// mprint(Serial, "string", int, long ...);
void Print(Stream&) {}
template <class H, class... Tail>
void Print(Stream& stream, H head, Tail... tail) {
  stream.print(head);
  Print(stream, tail...);
}

uint32_t SerialRead(int l){
	uint32_t v; // output
	char c = ' '; // input
	int i = 0; // amount of bytes read

	while(Serial.available() != 0){
		if (i == l + 1) break; // exit on last byte read

		c = Serial.read();
		if (c == '1') {
			v = v << 1;
			v |= 1;
			i++;
		}	
		if (c == '0') {
			v = v << 1;
			i++;
		}
	}
	return v;
}



