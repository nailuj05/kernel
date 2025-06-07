#include <stdint.h>
#include <stddef.h>

#define UART0_BASE 0x10000000
#define UART0_LSR (UART0_BASE + 0x05) 
#define UART0_RBR (UART0_BASE + 0x00) 

#define LSR_DATA_READY 0x01
#define LSR_THRE 0x20

volatile unsigned char* uart = (unsigned char *)UART0_BASE;

void putchar(char c) {
  while (!(*(volatile unsigned char*)(UART0_LSR) & LSR_THRE)) {}
  *uart = c;
}

char readchar() {
  while (!(*(volatile unsigned char*)UART0_LSR & LSR_DATA_READY));
  return *(volatile unsigned char*)UART0_RBR;
}

void readstring(char* buf) {
  char c;
  int i = 0;
  do {
    c = readchar();
    putchar(c);
    buf[i++] = c;
  } while(c != '\r');
  buf[i] = '\0';
}

void print(const char* str) {
	while(*str != '\0') {
		putchar(*str);
		str++;
	}
}
 
void kmain(void) {
  char buf[100] = {0};
	while(1) {
    print("> ");
    readstring(buf);
    print("\r\n");
    print(buf);
    print("\r\n");
	}
}
