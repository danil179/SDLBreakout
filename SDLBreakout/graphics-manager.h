#pragma once
#include "global.h"

class GraphicsManager {
 public:
  friend class Sprite;
  static SDL_Surface* getScreen();
  static void initalizeScreen(int width, int height, bool fullscreen);
  static int GetScreenWidth();
  static int GetScreenHeight();
  static void InitSdl();
  static SDL_Surface* LoadImageSurface(std::string filename, 
                                       Uint32 color = 0xFF00FF);
  static SDL_Rect InitRect(int x,int y ,int width,int height);
  static bool fullscreen_;

 private:
  static SDL_Surface* screen_;
  static int desk_width_;
  static int desk_height_;
  static int width_;
  static int height_;
  static bool init_sdl_;
};
