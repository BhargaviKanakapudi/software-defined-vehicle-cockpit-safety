#ifndef CPU_H
#define CPU_H

void set_runmask(unsigned mask);

void set_priority(int priority);

int get_current_cpu(void);

#define CPU0_MASK 0x1
#define CPU1_MASK 0x2
#define CPU2_MASK 0x4
#define CPU3_MASK 0x8

#endif
