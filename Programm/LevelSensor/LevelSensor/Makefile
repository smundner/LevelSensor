.SUFFIXES: .elf .hex

CC = avr-gcc
CFLAGS= -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000UL -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   
OFLAGS= -Wl,-Map="LevelSensor.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections
OBJECTS = main.o usart.o onewire.o ds18x20.o
MCU = attiny2313
TARGET = levelSensor

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex $< $@
	avr-size --mcu=$(MCU) -C $< 
$(TARGET).elf: $(OBJECTS)
	$(CC) -mmcu=$(MCU) $(OFLAGS) $(OBJECTS) -o $@
main.o: main.c main.h
	$(CC) -c -mmcu=$(MCU) $(CFLAGS) $< -o $@
%.o: %.c %.h
	$(CC) -c -mmcu=$(MCU) $(CFLAGS) $< -o $@
program: $(TARGET).hex
	avrdude -c jtag2isp -p t2313 -U flash:w:$(TARGET).hex -B 11
clean:
	rm *.elf *.o *.hex *.d 
