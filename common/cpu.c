#include <pthread.h>
#include <sched.h>
#include <stdint.h>
#include <string.h>

#include <sys/neutrino.h>
#include <sys/syspage.h>

#include "cpu.h"

void set_runmask(unsigned mask)
{
    ThreadCtl(
        _NTO_TCTL_RUNMASK,
        (void*)(uintptr_t)mask);
}

void set_priority(int priority)
{
    struct sched_param param;

    memset(&param, 0, sizeof(param));

    param.sched_priority = priority;

    pthread_setschedparam(
        pthread_self(),
        SCHED_FIFO,
        &param);
}

int get_current_cpu(void)
{
    return SYSPAGE_ENTRY(cpuinfo)->cpu;
}

