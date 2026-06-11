CC=qcc -Vgcc_ntoaarch64le

CFLAGS=-Wall -O2

COMMON=\
common/cpu.c \
common/gpio.c

all:

	$(CC) $(CFLAGS) \
	brake/brake.c \
	$(COMMON) \
	-o brake_app

	$(CC) $(CFLAGS) \
	cluster/cluster.c \
	$(COMMON) \
	-o cluster_app

	$(CC) $(CFLAGS) \
	media/media.c \
	$(COMMON) \
	-o media_app

	$(CC) $(CFLAGS) \
	watchdog/watchdog.c \
	$(COMMON) \
	-o watchdog_app

clean:
	rm -f \
	brake_app \
	cluster_app \
	media_app \
	watchdog_app