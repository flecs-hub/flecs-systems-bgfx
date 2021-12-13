#include "flecs_components_input.h"
#include <string.h>

void FlecsComponentsInputImport(ecs_world_t *world) {
  ECS_MODULE(world, FlecsComponentsInput);

  ecs_set_name_prefix(world, "ecs");

  ECS_IMPORT(world, FlecsMeta);

  ECS_META(world, ecs_key_state_t);
  ECS_META(world, ecs_mouse_coord_t);
  ECS_META(world, ecs_mouse_state_t);

  ecs_set_name_prefix(world, "Ecs");

  ECS_COMPONENT(world, EcsInput);

  ECS_EXPORT_COMPONENT(EcsInput);
}