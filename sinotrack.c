#include "sinotrack.h"
#include "crc16.h"

static float decode_coord(uint32_t raw)
{
    return (float)raw / 30000.0f / 60.0f;
}

uint8_t sinotrack_parse(const uint8_t *buf, uint16_t len, ST_Packet *out)
{
    if (len < 10)
        return 0;

    if (buf[0] != ST_HEADER_1 || buf[1] != ST_HEADER_2)
        return 0;

    if (buf[len - 2] != ST_FOOTER_1 || buf[len - 1] != ST_FOOTER_2)
        return 0;

    uint8_t pkt_len = buf[2];
    uint8_t proto   = buf[3];

    uint16_t crc_rx = (buf[len - 4] << 8) | buf[len - 3];
    uint16_t crc_calc = crc16_ccitt(&buf[2], len - 6);

    if (crc_rx != crc_calc)
        return 0;

    if (proto == ST_PROTO_GPS)
    {
        const uint8_t *p = &buf[4];

        out->type = ST_PACKET_GPS;

        out->gps.year   = 2000 + p[0];
        out->gps.month  = p[1];
        out->gps.day    = p[2];
        out->gps.hour   = p[3];
        out->gps.minute = p[4];
        out->gps.second = p[5];

        uint32_t lat_raw =
            (p[7] << 24) | (p[8] << 16) | (p[9] << 8) | p[10];

        uint32_t lon_raw =
            (p[11] << 24) | (p[12] << 16) | (p[13] << 8) | p[14];

        out->gps.latitude  = decode_coord(lat_raw);
        out->gps.longitude = decode_coord(lon_raw);

        out->gps.speed_kmh = p[15];
        out->gps.course    = ((p[16] << 8) | p[17]) & 0x03FF;

        return 1;
    }

    return 0;
}
