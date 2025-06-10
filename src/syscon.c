#include <stdint.h>
#include "syscon.h"
#include "uart.h"

void poweroff(void) {
  print("powering off\n");
  *(uint32_t *)SYSCON_ADDR = 0x5555;
}

void reboot(void) {
  print("powering off\n");
  *(uint32_t *)SYSCON_ADDR = 0x7777;
}
