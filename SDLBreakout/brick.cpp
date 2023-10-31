#include "brick.h"

Brick::Brick(BrickType type, int x, int y) : Object(TYPE_BRICK, "", 0xFF00FF, x, y) {
  this->set_y(y);
  this->set_x(x);
  this->brick_type = type;
  switch (type) {
    case PURPLE_BRICK:
      this->set_imagefile("Bricks/purple.png");
      break;
    case RED_BRICK:
      this->set_imagefile("Bricks/red.png");
      break;
    default:
      break;
  }
}

void Brick::OnCollision(Object* collider) {  
    switch (this->brick_type) {
    case RED_BRICK:
        this->set_imagefile("Bricks/purple.png");
        this->brick_type = PURPLE_BRICK;
        break;
    case PURPLE_BRICK:
        Powerup* pwr;
        if (rand() % 2 == 0)
          pwr = new Powerup(TYPE_PWR_PADDLE_UP, this->get_x(), this->get_y());
        else
          pwr = new Powerup(TYPE_PWR_PADDLE_DOWN, this->get_x(), this->get_y());
        ObjectManager::add(pwr);
        this->Destroy();
        break;
    }
}
