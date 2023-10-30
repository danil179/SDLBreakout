#pragma once
#include "global.h"
#include "object.h"

class Paddle: public Object {
 public:
  Paddle(int x, int y);
  void IncreaseSpeed(float x, float y);
  void Step();
  void BreakSpeed();
  void OnCollision(Object* collider) override;
  SDL_Rect image_cut_;
  int type_;
  float speedx_;
  float speedy_;
};
