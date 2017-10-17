#include "sprite.h"

Sprite::Sprite(std::string _image_file, SDL_Rect clip, Uint32 _color) {
  image_file_ = _image_file;
  background_color_ = _color;
  if(image_file_ != "")
  {
    image_ = GraphicsManager::LoadImageSurface(image_file_,background_color_);
  } else {
    image_ = NULL;
  }
  cut_image_ = clip;
}
SDL_Surface* Sprite::get_surface() {
  return this->image_;
}
SDL_Rect* Sprite::get_clip()
{
  if(cut_image_.h == 0 && cut_image_.w == 0 && cut_image_.x == 0 && cut_image_.y == 0) {
    return NULL;
  }
  return &cut_image_;
}
void Sprite::set_image(string file) {
  image_file_ = file;
  this->UpdateImage();
}
void Sprite::UpdateImage() {
  if(image_file_ != "") {
    this->image_ = GraphicsManager::LoadImageSurface(image_file_,background_color_);
  }
}
void Sprite::set_clip(SDL_Rect rec)
{
  this->cut_image_ = rec;
}
void Sprite::Draw(int x, int y) {
  SDL_Rect dst_screen;
  dst_screen.x= x;
  dst_screen.y = y;

  #ifdef DEBUG_DRAW
  string str = "X:" + Debug::IntToStr(x_) + " Y:" +  Debug::IntToStr(y_) + " Image file:" + this->image_file_;
  Debug::DebugLine(str);
  #endif

  SDL_BlitSurface(image_, this->get_clip(), GraphicsManager::screen_, &dst_screen);
}
void Sprite::Destroy() {
  SDL_FreeSurface(this->image_);
}
