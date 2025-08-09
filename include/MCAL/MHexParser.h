/*
 * HexParser.h
 *
 *  Created on: Aug 4, 2025
 *      Author: Ziad
 */

#ifndef HEXPARSER_H_
#define HEXPARSER_H_


#include "STD_TYPES.h"

typedef struct {
    u8 ByteCount;
    u16 Address;
    u8 RecordType;
    u8 Data[16]; // max 16 bytes of data per line
    u8 Checksum;
} HexRecord_t;

/**
 * @brief Parse a single line of Intel HEX and extract its components.
 *
 * @param line The input HEX line (starting with ':').
 * @param record Pointer to HexRecord_t structure to fill.
 * @return u8 0 on success, 1 on failure (invalid format or checksum).
 */
u8 HEXParser_ParseAndVerify(const char* line, HexRecord_t* record);

/**
 * @brief Verify the checksum of a parsed hex line.
 *
 * @param record Pointer to HexRecord_t structure.
 * @return u8 1 if valid, 0 if checksum mismatch.
 */
u8 HEXParser_VerifyChecksum(const HexRecord_t* record);


#endif /* HEXPARSER_H_ */
