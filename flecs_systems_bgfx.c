#include "flecs_systems_bgfx.h"

static int sdl_set_window(SDL_Window *_window) {
  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  if (!SDL_GetWindowWMInfo(_window, &wmi)) {
    return false;
  }

  bgfx_platform_data_t pd;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
  pd.ndt = wmi.info.x11.display;
  pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
  pd.ndt = NULL;
  pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
  pd.ndt = NULL;
  pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_STEAMLINK
  pd.ndt = wmi.info.vivante.display;
  pd.nwh = wmi.info.vivante.window;
#endif // BX_PLATFORM_
  pd.context = NULL;
  pd.backBuffer = NULL;
  pd.backBufferDS = NULL;
  bgfx_set_platform_data(&pd);

  return true;
}

static void BgfxSet(ecs_iter_t *it) {

  ecs_world_t *world = it->world;
  Sdl2Window *window = ecs_column(it, Sdl2Window, 1);
  EcsCanvas *canvas = ecs_column(it, EcsCanvas, 2);
  ecs_entity_t ecs_typeid(BgfxInit) = ecs_column_entity(it, 3);

  for (int32_t i = 0; i < it->count; i++) {
    uint32_t debug = BGFX_DEBUG_STATS;
    uint32_t reset = 0;

    if (!sdl_set_window(window[i].window)) {
      ecs_err("Error: %s\n", SDL_GetError());
    }

    bgfx_init_t init;
    bgfx_init_ctor(&init);

    bgfx_init(&init);
    bgfx_reset(window[i].actual_width, window[i].actual_height, reset,
               init.resolution.format);

    bgfx_set_debug(debug);
    bgfx_set_view_clear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x252525FF,
                        1.0f, 0);

    ecs_set(world, it->entities[i], BgfxInit, {.init = init});
  }
}

static void BgfxDestroy(ecs_iter_t *it) { bgfx_shutdown(); }

static void BgfxRender(ecs_iter_t *it) {
  ecs_world_t *world = it->world;
  Sdl2Window *window = ecs_column(it, Sdl2Window, 1);
  BgfxInit *init = ecs_column(it, BgfxInit, 2);

  int32_t i;
  for (i = 0; i < it->count; i++) {

    if (init[i].init.resolution.width != window[i].actual_width ||
        init[i].init.resolution.height != window[i].actual_height) {

      init[i].init.resolution.width = window[i].actual_width;
      init[i].init.resolution.height = window[i].actual_height;

      bgfx_reset(window[i].actual_width, window[i].actual_height, 0,
                 init[i].init.resolution.format);

      bgfx_set_view_rect(0, 0, 0, (uint16_t)window[i].actual_width,
                         (uint16_t)window[i].actual_height);
    }

    bgfx_touch(0);
    bgfx_frame(false);
  }
}

void FlecsSystemsBgfxImport(ecs_world_t *world) {

  ECS_MODULE(world, FlecsSystemsBgfx);

  ECS_IMPORT(world, FlecsSystemsSdl2);
  ECS_IMPORT(world, FlecsComponentsGui);

  ECS_COMPONENT(world, BgfxInit);

  ECS_SYSTEM(world, BgfxSet, EcsOnSet, flecs.systems.sdl2.window.Window,
             flecs.components.gui.Canvas,
             : BgfxInit);

  ECS_SYSTEM(world, BgfxDestroy, EcsUnSet, BgfxInit);
  ECS_SYSTEM(world, BgfxRender, EcsPostUpdate, flecs.systems.sdl2.window.Window,
             flecs.systems.bgfx.BgfxInit);
}