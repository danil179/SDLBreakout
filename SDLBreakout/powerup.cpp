#include "powerup.h"

Powerup::Powerup(PowerType type, int x, int y)
    : Object(TYPE_POWERUP, "", 0xFF00FF, x, y) {
  this->set_y(y);
  this->set_x(x);
  this->power_type = type;
  this->speed_= 100;
  switch (type) {
    case TYPE_PWR_PADDLE_UP:
      this->set_imagefile("pwr_up.png");
      break;
    case TYPE_PWR_PADDLE_DOWN:
      this->set_imagefile("pwr_down.png");
      break;
    default:
      break;
  }
}

void Powerup::Move() {
  int w = GraphicsManager::GetScreenWidth();
  int h = GraphicsManager::GetScreenHeight();
  set_y(get_y() + (speed_ / FRAMERATE) );
  if (get_y() > h) {
    this->Destroy();
  }
}
