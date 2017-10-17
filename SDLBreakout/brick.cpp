#include "brick.h"

Brick::Brick(BrickType type, int x, int y) : Object("", 0xFF00FF, x, y) {
  this->set_y(y);
  this->set_x(x);
  switch (type) {
    case BLUE_BRICK:
      this->set_imagefile("Bricks/blue.png");
      break;
    case RED_BRICK:
      this->set_imagefile("Bricks/red.png");
      break;
    default:
      break;
  }
}