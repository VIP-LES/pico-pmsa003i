// Copyright 2025 EWNB
// Licensed under the MIT License, see LICENSE for details.
// SPDX-License-Identifier: MIT

#ifndef PICO_PMSA003I_H
#define PICO_PMSA003I_H

#include "hardware/i2c.h"

namespace pico_pmsa003i {

  const uint8_t PMSA003I_ADDRESS = 0x12;
  const uint8_t PMSA003I_LENGTH = 32;

  class PMSA003I {
    private:

      i2c_inst *i2CInst;

    public:

      PMSA003I(i2c_inst *i2CInst);

      // Read new particulate concentration measurement data from the PMSA003I device and store in locations provided.
      // Returns 0 on success.
      // Returns 1 on I2C error, 2 on I2C timeout, 3 on bad frame start, 4 on bad frame length, 5 on bad checksum.
      int read(uint16_t &pm_1p0, uint16_t &pm_2p5, uint16_t &pm_10);
  };

}

#endif //PICO_PMSA003I_H
