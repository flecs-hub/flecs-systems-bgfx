#include "flecs_systems_sdl2.h"

static void Sdl2CreateWindow(ecs_iter_t *it) {
  EcsWindow *window = ecs_column(it, EcsWindow, 1);
  ecs_entity_t ecs_typeid(Sdl2Window) = ecs_column_entity(it, 2);

  int i;
  for (i = 0; i < it->count; i++) {
    ecs_entity_t e = it->entities[i];

    bool added = false;
    Sdl2Window *sdl_window = ecs_get_mut(it->world, e, Sdl2Window, &added);

    const char *title = window[i].title;
    if (!title) {
      title = "SDL2 window";
    }

    int x = SDL_WINDOWPOS_UNDEFINED;
    int y = SDL_WINDOWPOS_UNDEFINED;

    if (window[i].x) {
      x = window[i].x;
    }
    if (window[i].y) {
      y = window[i].y;
    }

    /* Create SDL Window with support for OpenGL and high resolutions */
    SDL_Window *wnd = SDL_CreateWindow(
        title, x, y, window[i].width, window[i].height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MAXIMIZED);

    if (!wnd) {
      ecs_err("SDL2 window creation failed: %s\n", SDL_GetError());
      break;
    }

    /* Set actual dimensions, as this may be a high resolution display */
    int32_t actual_width, actual_height;
    SDL_GL_GetDrawableSize(wnd, &actual_width, &actual_height);

    sdl_window->window = wnd;
    sdl_window->actual_width = actual_width;
    sdl_window->actual_height = actual_height;
  }
}

static void Sdl2DestroyWindow(ecs_iter_t *it) {
  Sdl2Window *window = ecs_column(it, Sdl2Window, 1);

  int i;
  for (i = 0; i < it->count; i++) {
    SDL_DestroyWindow(window[i].window);
  }
}

void FlecsSystemsSdl2WindowImport(ecs_world_t *world) {
  ECS_MODULE(world, FlecsSystemsSdl2Window);

  ecs_set_name_prefix(world, "Sdl2");

  ECS_COMPONENT(world, Sdl2Window);

  ECS_SYSTEM(world, Sdl2CreateWindow,
             EcsOnSet, [in] flecs.components.gui.Window, [out]
             : flecs.systems.sdl2.window.Window);

  ECS_SYSTEM(world, Sdl2DestroyWindow,
             EcsUnSet, [in] flecs.systems.sdl2.window.Window);

  ECS_EXPORT_COMPONENT(Sdl2Window);
}