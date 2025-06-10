RISCV_CC = riscv64-linux-gnu-gcc
RISCV_LD = riscv64-linux-gnu-ld
RISCV_AS = riscv64-linux-gnu-as
QEMU = qemu-system-riscv64

CFLAGS = -Wall -Wextra -c -mcmodel=medany -ffreestanding
LDFLAGS = -T linker/linker.ld -nostdlib
QEMUFLAGS = -machine virt -nographic -bios none -kernel kernel.elf -serial mon:stdio

all: kernel.elf

uart.o: src/uart.c
	$(RISCV_CC) $(CFLAGS) src/uart.c -o uart.o

syscon.o: src/syscon.c
	$(RISCV_CC) $(CFLAGS) src/syscon.c -o syscon.o

common.o: src/common.c
	$(RISCV_CC) $(CFLAGS) src/common.c -o common.o

kmain.o: src/kmain.c
	$(RISCV_CC) $(CFLAGS) src/kmain.c -o kmain.o

context.o: src/asm/context.S
	$(RISCV_AS) -c src/asm/context.S -o context.o

entry.o: src/asm/entry.S
	$(RISCV_AS) -c src/asm/entry.S -o entry.o

kernel.elf: kmain.o uart.o syscon.o common.o context.o entry.o
	$(RISCV_LD) $(LDFLAGS) kmain.o uart.o syscon.o common.o context.o entry.o -o kernel.elf

run: kernel.elf
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -f *.o kernel.elf
