#include "flecs_components_graphics.h"
#include <string.h>

void FlecsComponentsGraphicsImport(ecs_world_t *world) {
  ECS_MODULE(world, FlecsComponentsGraphics);

  ecs_set_name_prefix(world, "Ecs");

  ECS_COMPONENT(world, EcsCamera);
  ECS_COMPONENT(world, EcsDirectionalLight);
  ECS_COMPONENT(world, EcsRgb);
  ECS_COMPONENT(world, EcsRgba);
  ECS_COMPONENT(world, EcsSpecular);
  ECS_COMPONENT(world, EcsEmissive);

  ECS_EXPORT_COMPONENT(EcsCamera);
  ECS_EXPORT_COMPONENT(EcsDirectionalLight);
  ECS_EXPORT_COMPONENT(EcsRgb);
  ECS_EXPORT_COMPONENT(EcsRgba);
  ECS_EXPORT_COMPONENT(EcsSpecular);
  ECS_EXPORT_COMPONENT(EcsEmissive);
}