#include "object-manager.h"

// TODO: Implement
/*void ObjectManager::add(Object* pointer)
{
    objects.push_back(pointer);
}*/

void ObjectManager::add(Object* obj) { 
  ObjectManager::other_objects.push_back(obj);
}

void ObjectManager::remove_dead() {
  ObjectManager::other_objects.erase(std::remove_if(ObjectManager::other_objects.begin(),ObjectManager::other_objects.end(),[](Object* object){
    return object->IsDead();}), ObjectManager::other_objects.end());
}

std::vector<Object*> ObjectManager::get_objects() {
  return ObjectManager::other_objects;
}

std::vector<Object*> ObjectManager::other_objects;
