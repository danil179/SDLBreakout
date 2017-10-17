#pragma once
#include "global.h"

class Sprite {
 public:
  Sprite(std::string _image_file, SDL_Rect clip, Uint32 _color = 0xFF00FF);
  void Destroy();
  void Draw(int x, int y);
  SDL_Surface* get_surface();
  void set_image(std::string file);
  SDL_Rect* get_clip();
  void set_clip(SDL_Rect rec);

 private:
  void UpdateImage();
  SDL_Surface* image_;
  std::string image_file_;
  SDL_Rect cut_image_;
  Uint32 background_color_;
};