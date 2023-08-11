CC=../gcc/bin/arm-none-eabi-gcc

MACH=cortex-m4

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0

#LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_startup.ld -Wl,-Map=final.map

LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_startup.ld -Wl,-Map=final.map

all: main.o led.o stm32_startup.o syscalls.o final.elf 

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o: led.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: main.o led.o stm32_startup.o 
	$(CC) $(LDFLAGS) -o $@ $^

#syscalls.o
clean:
	rm -rf *.o *.elf

load:
	openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg


