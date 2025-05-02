# PMSA003I Particulate Sensor pico-sdk Library

Bare-bones library for reading values from a PMSA003I particle concentration sensor form a microcontroller using the [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) (C++).

Tested using the [Adafruit PMSA003I Air Quality Breakout](https://learn.adafruit.com/pmsa003i).

## Setup

To use this library, follow these steps.

### Git submodule

Add this repo as a Git submodule in your existing project.

```sh
git submodule add https://github.com/EWNB/pico-pmsa003i.git
git submodule update --init
```

### CMake import

Import this library in your project CMakeLists.txt file.

```cmake
add_subdirectory(pico-pmsa003i)
```

```cmake
target_link_libraries(${NAME}
  ...
  pico_pmsa003i
)
```

### C++ import

Import pico-pmsa003i.h in your code.

```c++
#include "pico-pmsa003i/pico-pmsa003i.h"
```

## Usage

Uing the library is quite simple.
Not surprising given how little there is of it.

A maximum I^2C clock frequency of approx. 100 kHz was found to be a safe speed for the sensor used in development.

```c++
// Initialise I^2C bus
i2c_init(I2C_PORT, 100000); // 100 kHz, limited by the PMSA003I

// Create PMSA003I particulates sensor object
pico_pmsa003i::PMSA003I pm_sens = pico_pmsa003i::PMSA003I(I2C_PORT);

// Read values from PMSA003I particulates sensor
uint16_t pm_1p0, pm_2p5, pm_10;
int pmsa003i_error = pm_sens.read(pm_1p0, pm_2p5, pm_10);
if (pmsa003i_error != 0) {
  printf("error executing PMSA003I read(): %i\n", pmsa003i_error);
} else {
  printf("successful PMSA003I read(): PM1.0 %u, PM2.5 %u, PM10 %u\n", pm_1p0, pm_2p5, pm_10);
}
```
