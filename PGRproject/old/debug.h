#pragma once

#define ASSERT(x) \
    if (!(x)) __debugbreak();
#define glcall(x) \
    x; \
    ASSERT(glCheckErrors())

bool glCheckErrors();