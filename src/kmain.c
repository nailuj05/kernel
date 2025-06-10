#include <stdint.h>
#include <stddef.h>

#include "uart.h"
#include "syscon.h"
#include "common.h"
#include "riscv.h"

#define STACK_SIZE 1024

reg task_stack[STACK_SIZE];
context ctx_os;
context ctx_task;

void task(void) {
  print("task program here\n");
  while(1) { };
}

void kmain(void) {
  char buf[100] = {0};
	while(strcmp(buf, "quit")) {
    print("> ");
    readstring(buf);
    print("\r\n");
    print(buf);
    print("\r\n");
  }


  print("switching to task\n");
  ctx_task.ra = (reg)task;
  ctx_task.sp = (reg)&task_stack[STACK_SIZE];

  sys_switch(&ctx_os, &ctx_task);
  
  poweroff();
}

