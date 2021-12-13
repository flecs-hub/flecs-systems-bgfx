#include "private.h"

int main(int argc, char *argv[]) {

  ecs_tracing_enable(1);
  ecs_tracing_color_enable(true);

  ecs_world_t *world = ecs_init_w_args(argc, argv);

  ECS_IMPORT(world, FlecsComponentsGraphics);
  ECS_IMPORT(world, FlecsComponentsGui);
  ECS_IMPORT(world, FlecsSystemsBgfx);

  ecs_entity_t window =
      ecs_set(world, 0, EcsWindow,
              {.title = "Flecs App", .width = 1366, .height = 768});

  ecs_entity_t canvas = ecs_set(world, window, EcsCanvas,
                                {
                                    .width = 1366,
                                    .height = 768,
                                    .background_color = {0.8, 0.8, 0.8},
                                    .ambient_light = {0.5, 0.5, 0.63},
                                });

  ecs_query_t *q_run_on_input = ecs_query_new(world, "OnInput");
  ecs_query_t *q_run_on_render = ecs_query_new(world, "OnRender");

  while (!ecs_should_quit(world)) {
    ecs_iter_t it = ecs_query_iter(q_run_on_input);
    while (ecs_query_next(&it)) {
      for (int i = 0; i < it.count; i++) {
        ecs_run(world, it.entities[i], 0, NULL);
      }
    }

    ecs_progress(world, 0);

    it = ecs_query_iter(q_run_on_render);
    while (ecs_query_next(&it)) {
      for (int i = 0; i < it.count; i++) {
        ecs_run(world, it.entities[i], 0, NULL);
      }
    }
  }

  return ecs_fini(world);
}