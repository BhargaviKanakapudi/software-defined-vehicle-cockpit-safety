#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "../common/cpu.h"
#include "../common/priorities.h"

void monitor_services(void)
{
    static uint64_t heartbeat = 0;

    heartbeat++;

    /*
     * Print only once every 5 seconds
     */

    if ((heartbeat % 5) == 0)
    {
        printf(
            "[WATCHDOG] system healthy (%lu)\n",
            (unsigned long)heartbeat);
    }
}

int main(void)
{
    set_runmask(CPU1_MASK);

    set_priority(PRIO_WATCHDOG);

    printf(
        "[WATCHDOG] Running on CPU%d\n",
        get_current_cpu());

    while (1)
    {
        monitor_services();

        sleep(1);
    }

    return 0;
}
