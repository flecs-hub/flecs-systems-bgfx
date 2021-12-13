#ifndef FLECS_SYSTEMS_IMGUI_H
#define FLECS_SYSTEMS_IMGUI_H

#include "flecs.h"
#include "flecs_systems_sdl2.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "imgui_impl_sdl.h"
#include "bgfx/c99_imgui_impl/imgui_impl_bgfx.h"

#ifndef flecs_systems_imgui_STATIC
#if flecs_systems_imgui_EXPORTS && (defined(_MSC_VER) || defined(__MINGW32__))
#define FLECS_SYSTEMS_IMGUI_API __declspec(dllexport)
#elif flecs_systems_imgui_EXPORTS
#define FLECS_SYSTEMS_IMGUI_API __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define FLECS_SYSTEMS_IMGUI_API __declspec(dllimport)
#else
#define FLECS_SYSTEMS_IMGUI_API
#endif
#else
#define FLECS_SYSTEMS_IMGUI_API
#endif

typedef struct ImguiContext {
  ImGuiContext *context;
} ImguiContext;

typedef struct FlecsSystemsImgui {
  ECS_DECLARE_COMPONENT(ImguiContext);
} FlecsSystemsImgui;

FLECS_SYSTEMS_IMGUI_API
void FlecsSystemsImguiImport(ecs_world_t *world);

#define FlecsSystemsImguiImportHandles(handles)                                \
  ECS_IMPORT_COMPONENT(handles, ImguiContext);

#endif