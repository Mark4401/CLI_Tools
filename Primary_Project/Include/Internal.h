#ifndef INTERNAL_H
#define INTERNAL_H

#include<iostream>
#include<stdint.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;

typedef Int32 Bool32;

typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef uint64_t Uint64;

#define internal static
#define global_var static
#define local_persist static

internal bool Global_Running;

#endif // !INTERNAL_H
