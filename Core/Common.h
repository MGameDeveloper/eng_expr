#pragma once


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <utility>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8  = uint8_t;

using s64 = int64_t;
using s32 = int32_t;
using s16 = int16_t;
using s8  = int8_t;

using f32 = float;
using f64 = double;


#define MAS_CLASS_DISABLE_COPY_SEMANTIC(T)\
    T(const T&)            = delete;      \
    T& operator=(const T&) = delete

#define MAS_CLASS_DISABLE_MOVE_SEMANTIC(T)\
    T(T&&)            = delete;           \
    T& operator=(T&&) = delete

#define MAS_CLASS_DISABLE_COPY_AND_MOVE_SEMANTIC(T)\
    MAS_CLASS_DISABLE_COPY_SEMANTIC(T);            \
    MAS_CLASS_DISABLE_MOVE_SEMANTIC(T)