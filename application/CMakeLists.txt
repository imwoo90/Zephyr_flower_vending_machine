#
# Copyright (c) 2019 Peter Bigot Consulting, LLC
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)

target_compile_definitions(app PRIVATE __RTTHREAD__)

add_subdirectory(src)
add_subdirectory(lib)