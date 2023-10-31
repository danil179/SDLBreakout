#pragma once
#include "global.h"
#include "sprite.h"

class Object {
 public:
  Object(ObjectType obj_type, std::string image_path, Uint32 color = 0xFF00FF,
         int x = 0, int y = 0, 
         SDL_Rect clip = SDL_Rect());
  ~Object();
  void Draw();
  void Destroy();
  bool IsDead();
  double get_x();
  double get_y();
  int get_width();
  int get_height();
  ObjectType get_type();
  void set_x(double x);
  void set_y(double y);
  void set_width(int w);
  void set_height(int h);
  void set_imagefile(std::string file);
  void set_clip(SDL_Rect clip);
  virtual void OnCollision(Object* collider);
  virtual void Move();
  SDL_Rect get_bounding_box();

 private:
  bool solid_;
  bool move_;
  bool dead_;
  ObjectType obj_type_;
  // TODO: Change to protected? (x and y)
  double x_;
  double y_;
  SDL_Rect* bounding_box_;
  Sprite image_;
};