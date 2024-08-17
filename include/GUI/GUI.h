// #pragma once
// #include "raylib.h"
// #define RAYGUI_IMPLEMENTATION
// #include "raygui.h"
// #include <vector>

// void initGUI(Texture* tex);
// void updateGUI();
// void drawGUI();
//
// bool isPosOnGui(Vector2 pos);
//
// std::vector<int> getAvailableTiles(Texture* tex);
//
//
// // Vars
// inline std::vector<Rectangle> g_vGuiBounds;
//
// inline bool g_bShowGUI;
// inline bool checked = false;
//
//
// // Structs
//
// struct IconButton
// {
//   Rectangle source;
//   Rectangle bounds;
// };
//
// struct TileSelection
// {
//   Rectangle bounds;
//   std::vector<IconButton> tileIcons;
//   Texture* atlas;
//
//   void init(Rectangle rect, Texture* texture);
//   void draw();
// };



// Få GUI til å ha tilgang på m_vAvailableTiles og m_atlas.
