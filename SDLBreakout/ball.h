#pragma once
#include "global.h"
#include "object.h"

class Ball : public Object {
 public:
  Ball(float s, int xpos, int ypos, float angle);
  void Bounce(SDL_Rect a, ObjectType ot);
  void Move() override;
  float get_speed();
  void set_speed(float s);
  void set_angle(float angle);
  void OnCollision(Object* collider) override;

 private:
  float speed_;
  float angle_;
};