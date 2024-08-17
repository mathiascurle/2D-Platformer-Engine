// #include "GUI.h"
// #include "Tiles.h"
// using namespace Tiles;

// void MyGUI::initGUI(Texture* tex)
// {
//   g_bShowGUI = true;
//   tileSelection.init(Rectangle{10, 70, 200, 400}, tex); 
//   // g_vGuiBounds.push_back();
//   g_vGuiBounds.shrink_to_fit();
// }
//
// void MyGUI::updateGUI()
// {
// }
//
// void MyGUI::drawGUI()
// {
//   DrawText("GUI", 10, 40, 20, GRAY);
//
//   // GuiWindowBox(Rectangle{200, 200, 200, 200}, "Window");
//   // GuiGroupBox(Rectangle{50, 50, 200, 200}, "GroupBox");
//   // Rectangle panelBounds = {10, 70, 200, 400};
//   // GuiPanel(panelBounds, "Available Tiles");
//   
//   tileSelection.draw();
// }
//
// bool MyGUI::isPosOnGui(Vector2 pos)
// {
//   for (Rectangle bounds : g_vGuiBounds)
//     if (CheckCollisionPointRec(pos, bounds))
//       return true;
//   return false;
// }
//
// std::vector<int> MyGUI::getAvailableTiles(Texture* tex)
// {
//   std::vector<int> returnObject;
//   Image image = LoadImageFromTexture(*tex);
//   Color pixelColor;
//   Vector2 vPos;
//   for (int i = 0; i<256; i++)
//   {
//     vPos = getTileAtlasPosV(i);
//     pixelColor = GetImageColor(image, vPos.x, vPos.y);
//     if (pixelColor.r != 0 &&
//         pixelColor.g != 0 &&
//         pixelColor.b != 0 &&
//         pixelColor.a != 0)
//       returnObject.push_back(i);
//   }
//   UnloadImage(image);
//   return returnObject;
// }
//
//
// // Structs \\
//
// void TileSelection::init(Rectangle rect, Texture* tex)
// {
//   bounds = rect;
//   atlas = tex;
//
//   // Add tiles to list of icons
//   for (int tile : getAvailableTiles(tex))
//   {
//     Vector2 pos = getTileAtlasPosV(tile);
//     tileIcons.push_back(IconButton{
//                         Rectangle{pos.x,
//                                   pos.y,
//                                   (float)g_iTileSize,
//                                   (float)g_iTileSize}, {0}});
//   }
//
//   // Set position for all tiles
//   int padding = 5;
//   int margin = 10;
//   int widthCount = (bounds.width - (2*margin)) / g_iTileSize;
//   margin = (bounds.width - (widthCount * g_iTileSize)) / 2;
//   int x = bounds.x+margin, y = bounds.y+35;
//   int n = 0;
//   for (IconButton tile : tileIcons)
//   {
//     if (x+g_iTileSize > bounds.x+bounds.width-margin/* n>=5 */)
//     {
//       x = bounds.x+margin;
//       y += g_iTileSize+padding;
//       n = 0;
//     }
//     tile.bounds = {(float)x, (float)y,
//       (float)g_iTileSize, (float)g_iTileSize};
//     x += g_iTileSize+padding;
//     n++;
//   }
//
//   g_vGuiBounds.push_back(bounds);
// }
//
// void TileSelection::draw()
// {
//   GuiPanel(bounds, "Available Tiles");
//   for (IconButton tile : tileIcons)
//   {
//     DrawTextureRec(*atlas,
//                    tile.source,
//                    Vector2 {tile.bounds.x, tile.bounds.y},
//                    WHITE);
//   }
// }
