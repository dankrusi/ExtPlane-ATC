#ifndef UTIL_H
#define UTIL_H

#define PLATFORM_UNKNOWN 0
#define PLATFORM_LINUX 1
#define PLATFORM_OSX 2
#define PLATFORM_WINDOWS 3

class Util
{
public:
    Util();

public:
    static int GetPlatform() {
        #if defined(Q_OS_LINUX)
            return PLATFORM_LINUX;
        #elif defined(Q_OS_MAC)
              return PLATFORM_OSX;
        #elif defined(Q_OS_WIN32)
               return PLATFORM_WINDOWS;
        #else
            return PLATFORM_UNKNOWN;
        #endif
    }
};

#endif // UTIL_H
