#ifndef BELLUM_OS_H
#define BELLUM_OS_H

// Mac and iOS
#if defined(__APPLE__) && !defined(ANDROID) // exclude android for binding generator.
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define BELLUM_IOS
#elif TARGET_OS_MAC
#define BELLUM_STANDALONE
#endif
#endif

// Android
#if defined(ANDROID)
#define BELLUM_ANDROID
#endif

// Win32
#if defined(_WIN32) || defined(WIN32) || defined(_WINDOWS)
#define BELLUM_STANDALONE
#endif

// Linux
#if defined(LINUX) && !defined(__APPLE__)
#define BELLUM_STANDALONE
#endif

#endif
