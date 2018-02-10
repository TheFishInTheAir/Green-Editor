//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once
#include <cstring>


#define STRINGIFY(s) #s

#define DBL_STRINGIFY(m) STRINGIFY(m)
#define MSTR(m) DBL_STRINGIFY(m)

#ifdef _WIN32

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#else

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#endif