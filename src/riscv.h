#ifndef RISCV_H
#define RISCV_H

#include <stdint.h>

#define reg uint64_t

typedef struct {
  reg ra;
  reg sp;

  // callee-saved
  reg s0;
  reg s1;
  reg s2;
  reg s3;
  reg s4;
  reg s5;
  reg s6;
  reg s7;
  reg s8;
  reg s9;
  reg s10;
  reg s11;
} context;

extern void sys_switch(context *old, context *new);

#endif 
