#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/neutrino.h>
#include <sys/syspage.h>

#include "../common/cpu.h"
#include "../common/ipc.h"
#include "../common/priorities.h"

static int g_chid;
static int g_coid;

static uint64_t g_brake_events = 0;

static double compute_latency(
    uint64_t start,
    uint64_t end)
{
    uint64_t cps =
        SYSPAGE_ENTRY(qtime)->cycles_per_sec;

    return ((double)(end - start)
        * 1000000.0) / cps;
}

void brake_warning_handler(void)
{
    /*
     * Simulated safety-critical action
     */

    g_brake_events++;

    /*
     * Print only every 5 brake events
     */

    if ((g_brake_events % 5) == 0)
    {
        printf(
            "[BRAKE] warning events=%lu\n",
            (unsigned long)g_brake_events);
    }
}

static void* interrupt_simulator(void* arg)
{
    struct sigevent event;

    while (1)
    {
        sleep(1);

        SIGEV_PULSE_INIT(
            &event,
            g_coid,
            PRIO_BRAKE_HANDLER,
            PULSE_BRAKE_EVENT,
            0);

        MsgDeliverEvent(0, &event);
    }

    return NULL;
}

int main(void)
{
    pthread_t sim_tid;

    struct _pulse pulse;

    uint64_t start_cycles;
    uint64_t end_cycles;

    double latency;

    static uint64_t latency_samples = 0;

    set_runmask(CPU0_MASK);

    set_priority(PRIO_BRAKE_HANDLER);

    printf(
        "[BRAKE] Running on CPU%d\n",
        get_current_cpu());

    g_chid = ChannelCreate(0);

    g_coid = ConnectAttach(
        0,
        0,
        g_chid,
        _NTO_SIDE_CHANNEL,
        0);

    pthread_create(
        &sim_tid,
        NULL,
        interrupt_simulator,
        NULL);

    while (1)
    {
        MsgReceivePulse(
            g_chid,
            &pulse,
            sizeof(pulse),
            NULL);

        start_cycles = ClockCycles();

        brake_warning_handler();

        usleep(100);

        end_cycles = ClockCycles();

        latency =
            compute_latency(
                start_cycles,
                end_cycles);

        latency_samples++;

        /*
         * Print latency every 5 interrupts
         */

        if ((latency_samples % 5) == 0)
        {
            printf(
                "[BRAKE] latency %.2f us\n",
                latency);
        }
    }

    return 0;
}
