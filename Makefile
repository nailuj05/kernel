RISCV_CC = riscv64-linux-gnu-gcc
RISCV_LD = riscv64-linux-gnu-ld
RISCV_AS = riscv64-linux-gnu-as
QEMU = qemu-system-riscv64

CFLAGS = -Wall -Wextra -c -mcmodel=medany -ffreestanding
LDFLAGS = -T linker.ld -nostdlib
QEMUFLAGS = -machine virt -nographic -bios none -kernel kernel.elf -serial mon:stdio

all: kernel.elf

kernel.o: kernel.c
	$(RISCV_CC) $(CFLAGS) kernel.c -o kernel.o

entry.o: entry.S
	$(RISCV_AS) -c entry.S -o entry.o

kernel.elf: kernel.o entry.o linker.ld
	$(RISCV_LD) $(LDFLAGS) kernel.o entry.o -o kernel.elf

run: kernel.elf
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -f *.o *.elf
