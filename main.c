#include "sinotrack.h"
#include <stdio.h>

uint8_t rx_buf[] = {
    0x78,0x78,0x1F,0x12,
    0x17,0x0C,0x0A,0x0B,0x2D,0x1E,
    0xC3,
    0x02,0x5F,0x4A,0x80,
    0x05,0x8B,0x3A,0x20,
    0x32,
    0x01,0xA6,
    0x00,0x02,
    0x8F,0x3C,
    0x0D,0x0A
};

int main(void)
{
    ST_Packet packet;

    if (sinotrack_parse(rx_buf, sizeof(rx_buf), &packet))
    {
        if (packet.type == ST_PACKET_GPS)
        {
            printf("Lat: %.6f\n", packet.gps.latitude);
            printf("Lon: %.6f\n", packet.gps.longitude);
            printf("Speed: %d km/h\n", packet.gps.speed_kmh);
        }
    }

    while (1) {}
}
