#include "flecs_systems_imgui.h"

static void ImguiSet(ecs_iter_t *it) {

  ecs_world_t *world = it->world;
  Sdl2Window *window = ecs_column(it, Sdl2Window, 1);
  EcsCanvas *canvas = ecs_column(it, EcsCanvas, 2);
  ecs_entity_t ecs_typeid(ImguiContext) = ecs_column_entity(it, 3);

  for (int32_t i = 0; i < it->count; i++) {

    ImGuiContext *context = igCreateContext(NULL);
    ImGuiIO *io = igGetIO();

    io->ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
    // Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io->ConfigFlags |=
        ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
                                          // / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    io->BackendFlags |= ImGuiBackendFlags_RendererHasViewports;

    igStyleColorsClassic(NULL);

    // ImGuiStyle *style = igGetStyle();
    // if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //   style->WindowRounding = 0.0f;
    //   style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    // }

    ImGui_Implbgfx_Init(255);

#if BX_PLATFORM_WINDOWS
    ImGui_ImplSDL2_InitForD3D(window->window);
#elif BX_PLATFORM_OSX
    ImGui_ImplSDL2_InitForMetal(window->window);
#elif BX_PLATFORM_LINUX
    ImGui_ImplSDL2_InitForOpenGL(window->window, NULL);
#endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX ? BX_PLATFORM_LINUX

    ecs_set(world, it->entities[i], ImguiContext, {.context = context});

    const char *version = igGetVersion();
    ecs_trace_1("ImGui %s initialized", version);
  }
}

static void ImguiDestroy(ecs_iter_t *it) {

  ImguiContext *context = ecs_column(it, ImguiContext, 1);

  ImGui_ImplSDL2_Shutdown();
  ImGui_Implbgfx_Shutdown();

  for (int32_t i = 0; i < it->count; i++) {
    igDestroyContext(context[i].context);
  }
}

static void ImguiRender(ecs_iter_t *it) {
  ecs_world_t *world = it->world;
  Sdl2Window *window = ecs_column(it, Sdl2Window, 1);
  ImguiContext *imgu_context = ecs_column(it, ImguiContext, 2);

  int32_t i;
  for (i = 0; i < it->count; i++) {

    ImGui_Implbgfx_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    igNewFrame();

    bool open = true;
    igShowDemoWindow(&open);

    igRender();
    ImGui_Implbgfx_RenderDrawLists(255, igGetDrawData());

    ImGuiIO *io = igGetIO();

    // Update and Render additional Platform Windows
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      igUpdatePlatformWindows();
      igRenderPlatformWindowsDefault(NULL, NULL);
    }
  }
}

void FlecsSystemsImguiImport(ecs_world_t *world) {

  ECS_TAG(world, OnRender);

  ECS_MODULE(world, FlecsSystemsImgui);
  ECS_IMPORT(world, FlecsSystemsSdl2);

  ECS_COMPONENT(world, ImguiContext);

  ECS_SYSTEM(world, ImguiSet, EcsOnSet, flecs.systems.sdl2.window.Window,
             flecs.components.gui.Canvas,
             : ImguiContext);

  ECS_SYSTEM(world, ImguiDestroy, EcsUnSet, ImguiContext);
  ECS_SYSTEM(world, ImguiRender, OnRender, flecs.systems.sdl2.window.Window,
             flecs.systems.imgui.ImguiContext);
}