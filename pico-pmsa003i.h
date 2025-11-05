// Copyright 2025 EWNB
// Licensed under the MIT License, see LICENSE for details.
// SPDX-License-Identifier: MIT

#ifndef PICO_PMSA003I_H
#define PICO_PMSA003I_H

#include "hardware/i2c.h"

namespace pico_pmsa003i {

constexpr uint8_t PMSA003I_ADDRESS = 0x12;
constexpr uint8_t PMSA003I_LENGTH = 32;

// All decoded PMSA003I output values
struct PMSA003I_Data {
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
};

class PMSA003I {
  private:

    i2c_inst *i2CInst;

  public:

    explicit PMSA003I(i2c_inst *i2CInst);

    // Reads a complete measurement frame and fills `out` with all 12 metrics.
    // Returns:
    //   0 = success
    //   1 = I2C error
    //   2 = I2C timeout
    //   3 = bad frame start
    //   4 = bad frame length
    //   5 = checksum mismatch
    int read(PMSA003I_Data &out);
};

}

#endif //PICO_PMSA003I_H
