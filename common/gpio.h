#ifndef GPIO_H
#define GPIO_H

int gpio_init_out(int pin);

int gpio_init_in(int pin);

void gpio_write(int pin, int value);

int gpio_read(int pin);

#endif
