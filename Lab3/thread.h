#ifndef __THREAD__
#define __THREAD__

// Lab 3
struct lock_t {
  uint locked;       // Is the lock held?
  struct cpu* cpu;
};
#endif
