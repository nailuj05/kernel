#ifndef UART_H
#define UART_H

#define UART0_BASE 0x10000000
#define UART0_LSR (UART0_BASE + 0x05) 
#define UART0_RBR (UART0_BASE + 0x00) 

#define LSR_DATA_READY 0x01
#define LSR_THRE 0x20

void putchar(char);
char readchar(void);
void readstring(char*);
void print(const char*);

#endif
