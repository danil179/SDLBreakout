#pragma once
#include "global.h"
#include "object.h"

// TODO: Implement
class ObjectManager {
 public:
  static void add(Object* pointer);
  static void remove_dead();
  static std::vector<Object*> get_objects();
 private:
  static std::vector<Object*> other_objects;
};