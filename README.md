# ODMR
Working code from laboratory on ODMR magnitometer 
## v0.1: initial working code

features:
- config files for ADC, AMP and overall sketch
- modulating signal for AMP via LEDC
- reset features for ADC and AMP
- message type control: single read, continuous conversion, continuous read (currently using continuous conversion)
- utils contain formated print function
- data averaging
-- iteration count control via ``it`` variable

planned: interrupt and appropriate handler for proper ADC read, use of microwave generator 

## v0.2: clean up
while i was against abstraction over SPI class, it have happened
over all refactoring and removal of unnecassery constants troughout the files
