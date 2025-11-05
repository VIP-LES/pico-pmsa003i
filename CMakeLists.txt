# Copyright 2025 EWNB
# Licensed under the MIT License, see LICENSE for details.
# SPDX-License-Identifier: MIT

add_library(pico_pmsa003i
    pico-pmsa003i.c
)

target_link_libraries(pico_pmsa003i
    hardware_i2c
    pico_stdlib
)

target_include_directories (pico_pmsa003i PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
