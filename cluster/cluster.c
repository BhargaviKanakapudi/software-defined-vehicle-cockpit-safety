#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "../common/cpu.h"
#include "../common/priorities.h"

void render_cluster(void)
{
    static uint64_t frame_count = 0;

    frame_count++;

    /*
     * Print every ~5 seconds
     *
     * 16000 us ≈ 60 FPS
     * 300 frames ≈ 5 sec
     */

    if ((frame_count % 300) == 0)
    {
        printf(
            "[CLUSTER] speedometer active frames=%lu\n",
            (unsigned long)frame_count);
    }
}

int main(void)
{
    set_runmask(CPU2_MASK);

    set_priority(PRIO_CLUSTER);

    printf(
        "[CLUSTER] Running on CPU%d\n",
        get_current_cpu());

    while (1)
    {
        render_cluster();

        usleep(16000);
    }

    return 0;
}
