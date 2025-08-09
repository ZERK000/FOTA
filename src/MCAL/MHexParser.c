/*
 * HexParser.c
 *
 *  Created on: Aug 4, 2025
 *      Author: Ziad
 */

#include "STD_TYPES.h"
#include "MCAL/MHexParser.h"


#define CHECKSUM_VALID   1
#define CHECKSUM_INVALID 0



/* :LL AAAA TT DD...DD CC
Where:

LL = number of data bytes (1 byte)

AAAA = address (2 bytes)

TT = record type (1 byte)

DD...DD = data bytes (LL bytes)

CC = checksum (1 byte)
*/

static u8 HexCharToByte(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0xFF; // Invalid
}


static u8 HexPairToByte(const char* hex) {
    return (HexCharToByte(hex[0]) << 4) | HexCharToByte(hex[1]);
}

u8 HEXParser_ParseAndVerify(const char* line, HexRecord_t* record) {
    if (line[0] != ':') return 1;

    record->ByteCount = HexPairToByte(&line[1]);
    record->Address = (HexPairToByte(&line[3]) << 8) | HexPairToByte(&line[5]);
    record->RecordType = HexPairToByte(&line[7]);

    for (u8 i = 0; i < record->ByteCount; i++) {
        record->Data[i] = HexPairToByte(&line[9 + i * 2]);
    }

    record->Checksum = HexPairToByte(&line[9 + record->ByteCount * 2]);

    return ((HEXParser_VerifyChecksum(record) == CHECKSUM_VALID) ? 0 : 1);
}

u8 HEXParser_VerifyChecksum(const HexRecord_t* record) {
    u16 sum = 0;
    sum += record->ByteCount;
    sum += (record->Address >> 8) & 0xFF;
    sum += record->Address & 0xFF;
    sum += record->RecordType;

    for (u8 i = 0; i < record->ByteCount; i++) {
        sum += record->Data[i];
    }

    sum += record->Checksum;

    return (((sum & 0xFF) == 0) ? CHECKSUM_VALID : CHECKSUM_INVALID);
}
