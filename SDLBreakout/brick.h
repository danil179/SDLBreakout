#pragma once
#include "global.h"
#include "object.h"

class Brick : public Object {
 public:
  Brick(BrickType type, int x, int y);
};