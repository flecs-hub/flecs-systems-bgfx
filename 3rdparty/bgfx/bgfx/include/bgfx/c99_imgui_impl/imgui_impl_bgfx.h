#ifndef IMGUI_IMPL_BGFX_H
#define IMGUI_IMPL_BGFX_H

#include "../c99/bgfx.h"

#define IMGUI_FLAGS_NONE        UINT8_C(0x00)
#define IMGUI_FLAGS_ALPHA_BLEND UINT8_C(0x01)

BGFX_C_API void ImGui_Implbgfx_Init(int view);
BGFX_C_API void ImGui_Implbgfx_Shutdown();
BGFX_C_API void ImGui_Implbgfx_NewFrame();
BGFX_C_API void ImGui_Implbgfx_RenderDrawLists(bgfx_view_id_t viewId, struct ImDrawData *draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
BGFX_C_API void ImGui_Implbgfx_InvalidateDeviceObjects();
BGFX_C_API bool ImGui_Implbgfx_CreateDeviceObjects();

#endif