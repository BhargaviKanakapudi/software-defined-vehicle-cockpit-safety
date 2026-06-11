#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "gpio.h"

static void write_file(
    const char* path,
    const char* value)
{
    int fd = open(path, O_WRONLY);

    if (fd < 0)
        return;

    write(fd, value, strlen(value));

    close(fd);
}

static int read_file(const char* path)
{
    char buf[8];

    int fd = open(path, O_RDONLY);

    if (fd < 0)
        return 0;

    read(fd, buf, sizeof(buf));

    close(fd);

    return (buf[0] == '1');
}

static void export_gpio(int pin)
{
    char buf[64];

    sprintf(buf, "%d", pin);

    write_file(
        "/sys/class/gpio/export",
        buf);
}

int gpio_init_out(int pin)
{
    char path[128];

    export_gpio(pin);

    sprintf(
        path,
        "/sys/class/gpio/gpio%d/direction",
        pin);

    write_file(path, "out");

    return 0;
}

int gpio_init_in(int pin)
{
    char path[128];

    export_gpio(pin);

    sprintf(
        path,
        "/sys/class/gpio/gpio%d/direction",
        pin);

    write_file(path, "in");

    return 0;
}

void gpio_write(int pin, int value)
{
    char path[128];

    sprintf(
        path,
        "/sys/class/gpio/gpio%d/value",
        pin);

    write_file(
        path,
        value ? "1" : "0");
}

int gpio_read(int pin)
{
    char path[128];

    sprintf(
        path,
        "/sys/class/gpio/gpio%d/value",
        pin);

    return read_file(path);
}
