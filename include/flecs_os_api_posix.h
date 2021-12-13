#ifndef FLECS_OS_API_POSIX_H
#define FLECS_OS_API_POSIX_H

/* This generated file contains includes for project dependencies */
/* Headers of public dependencies */
#include "flecs.h"

/* Convenience macro for exporting symbols */
#ifndef flecs_os_api_posix_STATIC
#if flecs_os_api_posix_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
#define FLECS_OS_API_POSIX_API __declspec(dllexport)
#elif flecs_os_api_posix_EXPORTS
#define FLECS_OS_API_POSIX_API __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define FLECS_OS_API_POSIX_API __declspec(dllimport)
#else
#define FLECS_OS_API_POSIX_API
#endif
#else
#define FLECS_OS_API_POSIX_API
#endif

#endif
#ifdef __cplusplus
extern "C" {
#endif

FLECS_OS_API_POSIX_API
void posix_set_os_api(void);

#ifdef __cplusplus
}
#endif