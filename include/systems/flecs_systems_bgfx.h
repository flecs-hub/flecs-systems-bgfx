#ifndef FLECS_SYSTEMS_BGFX_H
#define FLECS_SYSTEMS_BGFX_H

#include "flecs.h"
#include "flecs_components_gui.h"
#include "flecs_components_input.h"
#include "flecs_systems_sdl2.h"
#include "flecs_systems_imgui.h"
#include "bgfx/c99/bgfx.h"
#include <SDL2/SDL_syswm.h>

#ifndef flecs_systems_bgfx_STATIC
#if flecs_systems_bgfx_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
#define FLECS_SYSTEMS_BGFX_API __declspec(dllexport)
#elif flecs_systems_bgfx_EXPORTS
#define FLECS_SYSTEMS_BGFX_API __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define FLECS_SYSTEMS_BGFX_API __declspec(dllimport)
#else
#define FLECS_SYSTEMS_BGFX_API
#endif
#else
#define FLECS_SYSTEMS_BGFX_API
#endif

typedef struct BgfxInit {
  bgfx_init_t init;
} BgfxInit;

typedef struct FlecsSystemsBgfx {
  ECS_DECLARE_COMPONENT(BgfxInit);
} FlecsSystemsBgfx;

FLECS_SYSTEMS_BGFX_API
void FlecsSystemsBgfxImport(ecs_world_t *world);

#define FlecsSystemsBgfxImportHandles(handles)                                 \
  ECS_IMPORT_COMPONENT(handles, BgfxInit);

#endif