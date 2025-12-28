#ifndef SINOTRACK_H
#define SINOTRACK_H

#include <stdint.h>

#define ST_HEADER_1 0x78
#define ST_HEADER_2 0x78
#define ST_FOOTER_1 0x0D
#define ST_FOOTER_2 0x0A

#define ST_PROTO_LOGIN  0x01
#define ST_PROTO_GPS    0x12
#define ST_PROTO_STATUS 0x13

typedef struct
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;

    float latitude;
    float longitude;

    uint8_t speed_kmh;
    uint16_t course;
} ST_GPS_Data;

typedef enum
{
    ST_PACKET_INVALID = 0,
    ST_PACKET_GPS,
    ST_PACKET_LOGIN,
    ST_PACKET_STATUS
} ST_PacketType;

typedef struct
{
    ST_PacketType type;
    ST_GPS_Data gps;
} ST_Packet;

uint8_t sinotrack_parse(const uint8_t *buf, uint16_t len, ST_Packet *out);

#endif
