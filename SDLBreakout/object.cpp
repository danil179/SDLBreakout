#include "object.h"

Object::Object(ObjectType obj_type, std::string image_path, Uint32 color, int x, int y, 
               SDL_Rect clip) 
    : image_(image_path,clip,color) {
  bounding_box_ = new SDL_Rect();
  this->obj_type_ = obj_type;
  this->set_x(x);
  this->set_y(y);
  dead_ = false;
  if (image_path == "") {
    this->set_height(0);
    this->set_width(0);
  }
  if (image_.get_clip() == NULL) {
    if (image_.get_surface() != NULL) {
      this->set_height(image_.get_surface()->h);
      this->set_width(image_.get_surface()->w);
    }
  } else {
    this->set_height(clip.h);
    this->set_width(clip.w);
  }
}
void Object::set_imagefile(string file) {
  image_.set_image(file);
  SDL_Surface * sur = image_.get_surface();
  this->set_height(sur->h);
  this->set_width(sur->w);
}
void Object::set_clip(SDL_Rect clip) { 
  image_.set_clip(clip); 
}
void Object::OnCollision(Object* collider) {}
int Object::get_width() {
  return bounding_box_->w;
}
int Object::get_height() {
  return bounding_box_->h;
}
double Object::get_x() {
  return this->x_;
}
double Object::get_y() {
  return this->y_;
}
ObjectType Object::get_type() {
  return this->obj_type_;
}
void Object::Move() {
}
SDL_Rect Object::get_bounding_box() {
  return *bounding_box_;
}
void Object::set_x(double x) {
  this->x_ = x;
  bounding_box_->x = (int)x;
}
void Object::set_y(double y) {
  this->y_ = y;
  bounding_box_->y = (int)y;
}
void Object::set_width(int w) {
  bounding_box_->w = w;
}
void Object::set_height(int h) {
  bounding_box_->h = h;
}
void Object::Draw() {
  image_.Draw(round(this->x_),round(this->y_));
}
void Object::Destroy() {
  dead_=true;
  image_.Destroy();
  delete bounding_box_;
}
bool Object::IsDead() {
  return this->dead_;
}
Object::~Object() {
  // TODO: Release resources
  //SDL_FreeSurface(image.get_surface());
}