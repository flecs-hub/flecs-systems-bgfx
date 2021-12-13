#ifndef FLECS_SYSTEMS_SDL2_CONFIG_H
#define FLECS_SYSTEMS_SDL2_CONFIG_H

/* Headers of public dependencies */
#include "flecs.h"
#include "flecs_components_gui.h"
#include "flecs_components_input.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

/* Convenience macro for exporting symbols */
#ifndef flecs_systems_sdl2_STATIC
#if flecs_systems_sdl2_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
#define FLECS_SYSTEMS_SDL2_API __declspec(dllexport)
#elif flecs_systems_sdl2_EXPORTS
#define FLECS_SYSTEMS_SDL2_API __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define FLECS_SYSTEMS_SDL2_API __declspec(dllimport)
#else
#define FLECS_SYSTEMS_SDL2_API
#endif
#else
#define FLECS_SYSTEMS_SDL2_API
#endif

#endif
