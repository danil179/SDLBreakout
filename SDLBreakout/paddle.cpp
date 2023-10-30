#include "paddle.h"

Paddle::Paddle(int x, int y)
    : Object(TYPE_PADDLE, "breakout_tiles.png",0x000000,x,y,
             GraphicsManager::InitRect(0, 240, 112, 24)) {
  this->speedx_ = 0;
  this->speedy_ = 0;

  this->type_ = 1;

  switch (type_) {
  case 1:
    this->image_cut_.h = 24;
    this->image_cut_.w = 96;
    this->image_cut_.x = 0;
    this->image_cut_.y = 200;
    break;
  case 2:
    this->image_cut_.h = 24;
    this->image_cut_.w = 112;
    this->image_cut_.x = 0;
    this->image_cut_.y = 240;
    break;
  case 3:
    this->image_cut_.h = 24;
    this->image_cut_.w = 128;
    this->image_cut_.x = 0;
    this->image_cut_.y = 280;
    break;
  }

  breakout_debug::DebugLine("Paddle width:"+ breakout_debug::IntToStr(this->get_width()));
  breakout_debug::DebugLine("Paddle height:"+ breakout_debug::IntToStr(this->get_height()));
}
void Paddle::Step()
{
  int x,y;
  SDL_GetMouseState(&x,&y);
  if (x < 0) {
    x = 0;
  } 
  if (x > GraphicsManager::GetScreenWidth()) {
    x = GraphicsManager::GetScreenWidth() - get_width();
  }
  if (y <0 ) {
    y=0;
  }
  if (y > GraphicsManager::GetScreenHeight()) {
    x = GraphicsManager::GetScreenHeight()- get_height();
  }
  if (get_x() == x) {
    BreakSpeed();
  } else {
    if (get_x() + (get_width()/2) < x) {
      if (speedx_ < 0) {
        BreakSpeed();
      }
      IncreaseSpeed((float)PADDLE_INC_SPEED, 0);
      if (speedx_ + (get_x() + (get_width()/2)) >= x) {
        set_x(x - (get_width()/2));
        BreakSpeed();
      }
    } else if (get_x() + (get_width()/2) > x) {
      if (speedx_ > 0) {
        BreakSpeed();
      }
      IncreaseSpeed(-1 * (float)PADDLE_INC_SPEED, 0);
      if (speedx_ + (get_x() + (get_width()/2)) <= x) {
        set_x(x - (get_width()/2));
        BreakSpeed();
      }
    }
  }

  #ifdef  DEBUG_SPEED
  breakout_debug::DebugLine("\npaddle speed x:" + 
                            breakout_debug::IntToStr((int)speedx_) + "\n");
  #endif

  set_x(get_x() + speedx_ );
  set_y(get_y() + speedy_ );
}
void Paddle::IncreaseSpeed(float x, float y) {
  this->speedx_ += x;
  this->speedy_ += y;
}
void Paddle::BreakSpeed() {
  this->speedx_ = 0;
  this->speedy_ = 0;
}

void Paddle::OnCollision(Object* collider)
{
    
}
