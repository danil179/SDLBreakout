#include "sdl-manager.h"

SdlManager::SdlManager() {
  SDL_Init(SDL_INIT_EVERYTHING);
  GraphicsManager::initalizeScreen(0, 0, true);	
}