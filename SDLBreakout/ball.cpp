#include "ball.h"

Ball::Ball(float s, int xpos, int ypos, float angle) 
    : Object("breakout_tiles.png", 0x000000, xpos, ypos, 
             GraphicsManager::InitRect(160, 200, 16, 16)) {
  speed_ = s;
  this->angle_ = angle;
  breakout_debug::DebugLine("Ball width:" + 
                            breakout_debug::IntToStr(this->get_width()));
  breakout_debug::DebugLine("Ball height:" + 
                            breakout_debug::IntToStr(this->get_height()));
}
void Ball::Move() {
  int w = GraphicsManager::GetScreenWidth();
  int h = GraphicsManager::GetScreenHeight();

  // Borders collison check
  if (get_x()  <= 0 || (get_x()+get_width()) >= w) {
    angle_ = 180 - angle_;
    if ((int)get_x() <= 0) {
      this->set_x(1);
    } else {
      this->set_x(w - 1 - this->get_width());
    }	
  }
  if (get_y() <= 0) {
    angle_ = 360 - angle_;
    this->set_y(1);	
    // No other case like x because ball can fall from the window when the paddle misses it
  }
  set_x(get_x() + (speed_/FRAMERATE) * cos(deg_to_rad(angle_)));
  set_y(get_y() + (speed_/FRAMERATE) * -sin(deg_to_rad(angle_)));
}
void Ball::Bounce(SDL_Rect a, ObjectType ot) {
  int x2 = a.x;
  int y2 = a.y;
  int w2 = a.w;
  int h2 = a.h;

  bool up = false, left = false, right = false, down = false;

  int x1 = this->get_bounding_box().x;
  int y1 = this->get_bounding_box().y;
  int w1 = this->get_bounding_box().w;
  int h1 = this->get_bounding_box().h;

  if ((x1+w1) >= x2 && x1 <= x2) {  //Left Side
    left=true;
  } else if ((x1+w1) >= (x2+w2) && x1 <= (x2+w2)) {  //Right Side
    right = true;
  }

  if ((y1+h1) >= y2 && y1 <= y2) {  //Up Side
    up=true;
  } else if ((y1+h1) >= (y2+h2) && y1 <= (y2+h2)) {  //Down Side
    down=true;
  }

  // Constants are directions
  // TODO: Implement constants at global
  if (ot == TYPE_PADDLE && up) {
    float percent = (float)( (x1+ w1 ) - x2 )/w2;
    angle_ =  abs(percent * (-90) + BALL_PADDLE_ANGLE_LEFT);
  } else if (left && up) {
    angle_ = 135;
  } else if(left && down) {
    angle_ = -135;
  } else if(right && up) {
    angle_ = 45;
  } else if(right && down) {
    angle_ = -45;
  } else if( up || down) {
    angle_ = -angle_;
  } else if(right || left) {
    angle_ = -angle_ + 180;
  }

  // Some random addition to the angle (max 10 degrees)
  angle_ += rand() % 20 - 10;
  Move();
}
float Ball::get_speed() {
  return this->speed_;
}
void Ball::set_speed(float s) {
  this->speed_ = s;
}
void Ball::set_angle(float angle) {
  this->angle_ = angle;
}