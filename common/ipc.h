#ifndef IPC_H
#define IPC_H

/*
 * ============================================================================
 *  QNX Cockpit IPC Definitions
 * ============================================================================
 */

/*
 * Channel IDs
 */

#define COCKPIT_BRAKE_CHID      10
#define COCKPIT_HEARTBEAT_CHID  20

/*
 * Pulse Codes
 */

#define PULSE_BRAKE_EVENT       0x50
#define PULSE_HEARTBEAT         0x60

/*
 * Heartbeat Timing
 */

#define HEARTBEAT_INTERVAL_SEC  1
#define HEARTBEAT_TIMEOUT_SEC   3

/*
 * Safety Events
 */

#define EVENT_BRAKE_WARNING     1
#define EVENT_ADAS_ALERT        2
#define EVENT_CLUSTER_UPDATE    3

/*
 * Multimedia Events
 */

#define EVENT_MEDIA_FRAME       10
#define EVENT_MEDIA_OVERLOAD    11

#endif
