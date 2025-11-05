// Copyright 2025 EWNB
// Licensed under the MIT License, see LICENSE for details.
// SPDX-License-Identifier: MIT

#ifndef PICO_PMSA003I_H
#define PICO_PMSA003I_H

#include "hardware/i2c.h"
#include <stdint.h>

#define PMSA003I_ADDRESS 0x12
#define PMSA003I_LENGTH  32

typedef struct {
    uint16_t pm10_standard_ug_m3;
    uint16_t pm25_standard_ug_m3;
    uint16_t pm100_standard_ug_m3;
    uint16_t pm10_environmental_ug_m3;
    uint16_t pm25_environmental_ug_m3;
    uint16_t pm100_environmental_ug_m3;
    uint16_t particulate_03um_per_01L;
    uint16_t particulate_05um_per_01L;
    uint16_t particulate_10um_per_01L;
    uint16_t particulate_25um_per_01L;
    uint16_t particulate_50um_per_01L;
    uint16_t particulate_100um_per_01L;
} pmsa003i_data_t;

// Initialize the sensor with a chosen I2C instance.
void pmsa003i_init(i2c_inst_t *i2c_inst);

// Read a full data frame into the provided struct.
// Returns 0 on success.
// Returns 1 on I2C error, 2 on timeout, 3 on bad frame start,
// 4 on bad frame length, 5 on checksum fail.
int pmsa003i_read(pmsa003i_data_t *out);

#endif