#pragma once
#include "global.h"
#include "object.h"
#include "object-manager.h"

class Powerup : public Object {
 public:
  Powerup(PowerType type, int x, int y);
  void Move() override;
  // Make this private
  PowerType power_type;

 private:
  float speed_;
};