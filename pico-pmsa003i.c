// Copyright 2025 EWNB
// Licensed under the MIT License, see LICENSE for details.
// SPDX-License-Identifier: MIT

#include "pico-pmsa003i.h"
#include "hardware/i2c.h"

// Static pointer to selected I2C instance
static i2c_inst_t *pmsa003i_i2c = NULL;

// Initialize the PMSA003I driver with the chosen I2C instance
void pmsa003i_init(i2c_inst_t *i2c_inst) {
    pmsa003i_i2c = i2c_inst;
}

// Read all data from the PMSA003I device
// Returns:
//  0  = success
//  1  = generic I2C failure
//  2  = timeout
//  3  = unexpected frame start
//  4  = unexpected frame length
//  5  = checksum fail
int pmsa003i_read(pmsa003i_data_t *out) {
    if (!pmsa003i_i2c || !out) {
        return 1;  // invalid state or argument
    }

    // Read all data from device
    uint8_t data[PMSA003I_LENGTH];
    int ret = i2c_read_timeout_us(
        pmsa003i_i2c,
        PMSA003I_ADDRESS,
        data,
        PMSA003I_LENGTH,
        false,
        1000 * PMSA003I_LENGTH
    );

    if (ret != PMSA003I_LENGTH) {
        if (ret == PICO_ERROR_GENERIC) {
            return 1;
        }
        if (ret == PICO_ERROR_TIMEOUT) {
            return 2;
        }
        return 1;  // unknown I2C failure
    }

    // Check for data errors
    if (data[0] != 0x42 || data[1] != 0x4D) {
        return 3;  // unexpected frame start
    }
    if (data[2] != 0x00 || data[3] != 0x1C) {
        return 4;  // unexpected frame length
    }

    // Compute checksum
    uint16_t sum = 0;
    for (int i = 0; i < PMSA003I_LENGTH - 2; i++) {
        sum += data[i];
    }
    if (sum != ((data[PMSA003I_LENGTH - 2] << 8) + data[PMSA003I_LENGTH - 1])) {
        return 5;  // checksum fail
    }

    // Decode all fields per PMSA003I datasheet
    out->pm10_standard_ug_m3       = (data[4]  << 8) | data[5];
    out->pm25_standard_ug_m3       = (data[6]  << 8) | data[7];
    out->pm100_standard_ug_m3      = (data[8]  << 8) | data[9];
    out->pm10_environmental_ug_m3  = (data[10] << 8) | data[11];
    out->pm25_environmental_ug_m3  = (data[12] << 8) | data[13];
    out->pm100_environmental_ug_m3 = (data[14] << 8) | data[15];
    out->particulate_03um_per_01L  = (data[16] << 8) | data[17];
    out->particulate_05um_per_01L  = (data[18] << 8) | data[19];
    out->particulate_10um_per_01L  = (data[20] << 8) | data[21];
    out->particulate_25um_per_01L  = (data[22] << 8) | data[23];
    out->particulate_50um_per_01L  = (data[24] << 8) | data[25];
    out->particulate_100um_per_01L = (data[26] << 8) | data[27];

    return 0;
}