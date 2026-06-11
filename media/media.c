#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sched.h>

#include "../common/cpu.h"
#include "../common/priorities.h"
#include "../common/gpio.h"
#include "../common/gpio_pins.h"

static volatile int g_high_load = 0;

static void normal_media_load(void)
{
    volatile uint64_t x = 0;

    for (uint64_t i = 0;
         i < 200000000ULL;
         i++)
    {
        x += i;

        if ((i % 5000000ULL) == 0)
        {
            sched_yield();
        }
    }
}

static void extreme_media_load(void)
{
    volatile uint64_t x = 0;

    /*
     * Massive CPU stress
     */

    for (uint64_t i = 0;
         i < 3000000000ULL;
         i++)
    {
        x += i;
    }
}

static void* button_monitor_thread(void* arg)
{
    int last_state = 0;

    gpio_init_in(BUTTON_MEDIA_LOAD);

    while (1)
    {
        int state =
            gpio_read(BUTTON_MEDIA_LOAD);

        /*
         * Rising edge detect
         */

        if (state && !last_state)
        {
            g_high_load =
                !g_high_load;

            if (g_high_load)
            {
                printf(
                    "[MEDIA] EXTREME LOAD ENABLED\n");
            }
            else
            {
                printf(
                    "[MEDIA] NORMAL LOAD ENABLED\n");
            }
        }

        last_state = state;

        usleep(50000);
    }

    return NULL;
}

int main(void)
{
    pthread_t button_tid;
    uint64_t frames = 0;

    set_runmask(CPU1_MASK);

    set_priority(PRIO_MEDIA);

    gpio_init_out(LED_MEDIA);

    printf(
        "[MEDIA] Running CPU%d\n",
        get_current_cpu());

    pthread_create(
        &button_tid,
        NULL,
        button_monitor_thread,
        NULL);

    while (1)
    {
        gpio_write(LED_MEDIA, 1);

        if (g_high_load)
        {
            extreme_media_load();
        }
        else
        {
            normal_media_load();
        }

        gpio_write(LED_MEDIA, 0);

        frames++;

        if ((frames % 10) == 0)
        {
            printf(
                "[MEDIA] frames=%lu mode=%s\n",
                (unsigned long)frames,
                g_high_load ?
                "EXTREME" :
                "NORMAL");
        }
    }

    return 0;
}
