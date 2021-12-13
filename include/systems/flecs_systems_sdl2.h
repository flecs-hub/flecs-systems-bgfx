#ifndef FLECS_SYSTEMS_SDL2_H
#define FLECS_SYSTEMS_SDL2_H

#include "flecs_systems_sdl2_config.h"
#include "sdl_window.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FlecsSystemsSdl2 {
  ECS_DECLARE_ENTITY(Sdl);
} FlecsSystemsSdl2;

FLECS_SYSTEMS_SDL2_API
void FlecsSystemsSdl2Import(ecs_world_t *world);

#define FlecsSystemsSdl2ImportHandles(handles) ECS_IMPORT_ENTITY(handles, Sdl);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

namespace flecs {
namespace systems {

class sdl2 : FlecsSystemsSdl2 {
public:
  sdl2(flecs::world &ecs) {
    FlecsSystemsSdl2Import(ecs.c_ptr());

    ecs.module<flecs::systems::sdl2>();
  }
};

} // namespace systems
} // namespace flecs

#endif

#endif