#ifndef SPIDERNET_PLATFORM_H
#define SPIDERNET_PLATFORM_H

//system
#define SPIDERNET_PLATFORM_WINDOWS 1
#define SPIDERNET_PLATFORM_LINUX 2
#define SPIDERNET_PLATFORM_UNIX 3
#define SPIDERNET_PLATFORM_APPLE 4

//compiler
#define SPIDERNET_COMPILER_MSVC 1
#define SPIDERNET_COMPILER_GCC 2
#define SPIDERNET_COMPILER_CLANG 3

#if defined _WIN32 || _WIN64
#define SPIDERNET_PLATFORM SPIDERNET_PLATFORM_WINDOWS
#elif defined __linux || __linux__
#define SPIDERNET_PLATFORM SPIDERNET_PLATFORM_LINUX
#endif // _linux || _linux_

#if defined __APPLE__
#define SPIDER_PLATFORM SPIDERNET_PLATFORM_APPLE
#endif // __APPLE_

#if defined __unix || __unix__
#define SPIDER_PLATFORM SPIDERNET_PLATFORM_UNIX
#endif // _unix || _unix_

#ifdef _MSC_VER
#define SPIDERNET_COMPILER SPIDERNET_COMPILER_MSVC
#endif // _MSC_VER

#ifdef _GNUC_
#define SPIDERNET_COMPILER SPIDERNET_COMPILER_GCC
#endif // _GNUC_

#ifdef __clang__
#define SPIDERNET_COMPILER SPIDER_COMPILER_CLANG
#endif // __clang__

// For marking functions as deprecated
#if SPIDERNET_COMPILER == SPIDERNET_COMPILER_MSVC
#define SPIDERNET_DEPRECATED __declspec(deprecated)
#elif SPIDERNET_COMPILER == SPIDERNET_COMPILER_GCC || OGRE_COMPILER == SPIDER_COMPILER_CLANG
#define SPIDERNET_DEPRECATED __attribute__((deprecated))
#else
#pragma message("WARNING: You need to implement SPIDERNET_DEPRECATED for this compiler")
#define SPIDERNET_DEPRECATED
#endif

#if SPIDERNET_COMPILER == SPIDERNET_COMPILER_MSVC
#define SPIDERNET_NO_RETURN __declspec(noreturn)
#elif SPIDERNET_COMPILER == SPIDERNET_COMPILER_GCC || OGRE_COMPILER == SPIDER_COMPILER_CLANG
#define SPIDERNET_NO_RETURN __attribute__((noreturn))
#else
#pragma message("WARNING: You need to implement SPIDERNET_NO_RETURN for this compiler")
#define SPIDERNET_NO_RETURN
#endif

#ifdef SPIDERNET_DEBUG_MODE
#undef SPIDERNET_DEBUG_MODE
#endif //  SPIDERNET_DEBUG_MODE

#if defined(_DEBUG) && !defined(NDEBUG)
#define SPIDERNET_DEBUG_MODE 1
#else
#define SPIDERNET_DEBUG_MODE 0
#endif // (_DEBUG) && !defined(NDEBUG)

typedef signed char int8;
typedef short int16;
typedef int int32;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#if SPIDERNET_COMPILER == SPIDERNET_COMPILER_MSVC
typedef unsigned __int64 uint64;
typedef __int64 int64;
#else
typedef long long int64;
typedef unsigned long long uint64;
#endif

#endif