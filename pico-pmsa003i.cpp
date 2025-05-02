// Copyright 2025 EWNB
// Licensed under the MIT License, see LICENSE for details.
// SPDX-License-Identifier: MIT

#include "pico-pmsa003i.h"

namespace pico_pmsa003i {

  PMSA003I::PMSA003I(i2c_inst *i2CInst) : i2CInst(i2CInst) {  }

  int PMSA003I::read(uint16_t &pm_1p0, uint16_t &pm_2p5, uint16_t &pm_10) {
    // Read all data from device
    uint8_t data[PMSA003I_LENGTH];
    int ret = i2c_read_timeout_us(this->i2CInst, PMSA003I_ADDRESS, data, PMSA003I_LENGTH, false, 1000 * PMSA003I_LENGTH);
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
    if (data[0] != 0x42 || data[1] != 0x4d) {
      return 3;  // unexpected frame start
    }
    if (data[2] != 0x00 || data[3] != 0x1c) {
      return 4;  // unexpected frame length
    }
    uint16_t sum = 0;
    for (int i = 0; i < PMSA003I_LENGTH - 2; i++) {
      sum += data[i];
    }
    if (sum != (data[PMSA003I_LENGTH-2] << 8) + data[PMSA003I_LENGTH-1]) {
      return 5; // checksum fail
    }

    // Store environmental PM values
    pm_1p0  = (data[0xa] << 8) + data[0xb];
    pm_2p5  = (data[0xc] << 8) + data[0xd];
    pm_10   = (data[0xe] << 8) + data[0xf];

    return 0;
  }

}
