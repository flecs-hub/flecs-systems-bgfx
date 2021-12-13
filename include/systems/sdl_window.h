#ifndef FLECS_SYSTEMS_SDL2_WINDOW_H
#define FLECS_SYSTEMS_SDL2_WINDOW_H

#include "flecs_systems_sdl2_config.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Sdl2Window {
  SDL_Window *window;
  int actual_width;
  int actual_height;
} Sdl2Window;

typedef struct FlecsSystemsSdl2Window {
  ECS_DECLARE_COMPONENT(Sdl2Window);
} FlecsSystemsSdl2Window;

FLECS_SYSTEMS_SDL2_API
void FlecsSystemsSdl2WindowImport(ecs_world_t *world);

#define FlecsSystemsSdl2WindowImportHandles(handles)                           \
  ECS_IMPORT_COMPONENT(handles, Sdl2Window);

#ifdef __cplusplus
}
#endif
#endif