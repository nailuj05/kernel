#include "uart.h"

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
  while((c = readchar()) != '\r') buf[i++] = c;
  buf[i] = '\0';
}

void print(const char* str) {
	while(*str != '\0') {
		putchar(*str);
		str++;
	}
}
