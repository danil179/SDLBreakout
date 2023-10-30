#pragma once
#include "global.h"
#include "object.h"

class Brick : public Object {
 public:
  Brick(BrickType type, int x, int y);
  void OnCollision(Object* collider) override;
  BrickType brick_type;
};