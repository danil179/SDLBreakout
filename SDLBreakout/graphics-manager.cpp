#include "graphics-manager.h"

void GraphicsManager::initalizeScreen(int new_width, int new_height , bool is_fullscreen) {
  if (desk_width_ == 0 && desk_height_ == 0) {
    if (is_fullscreen == true) {
      screen_ = SDL_SetVideoMode(0, 0, SCREEN_BPP, SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);
      desk_width_ = screen_->w;	
      desk_height_ = screen_->h;
      width_ = screen_->w;	
      height_ = screen_->h;
    } else {
      screen_ = SDL_SetVideoMode(0, 0, SCREEN_BPP, SDL_DOUBLEBUF | SDL_SWSURFACE| SDL_RESIZABLE);
      desk_width_ = screen_->w;	
      desk_height_ = screen_->h;
    }
  } else {
    if (!is_fullscreen) {
      screen_ = SDL_SetVideoMode(new_width, new_height, SCREEN_BPP, SDL_DOUBLEBUF | SDL_RESIZABLE);
      width_ = screen_->w;	
      height_ = screen_->h;
      fullscreen_ = false;
    } else {
      screen_ = SDL_SetVideoMode(new_width, new_height, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN);
      width_ = screen_->w;	
      height_ = screen_->h;
      stringstream out;
      out << width_ << ":" << height_;
      breakout_debug::DebugLine(out.str());
      fullscreen_ = true;
    }
  }
}
SDL_Surface * GraphicsManager::getScreen() {
  return GraphicsManager::screen_;
}
int GraphicsManager::GetScreenWidth() {
  return GraphicsManager::width_;
}
int GraphicsManager::GetScreenHeight() {
  return GraphicsManager::height_;
}
void GraphicsManager::InitSdl() {
  if (SDL_Init( SDL_INIT_EVERYTHING ) == -1 || init_sdl_ == true) { 
    return; 
  }
  init_sdl_ = true;
  return;
}
SDL_Surface* GraphicsManager::LoadImageSurface(std::string filename, Uint32 color) { 
  string m_fn = filename;
  filename.insert(0,"../"+IMAGES_FOLDER+"/");
  SDL_Surface* loaded_image = NULL; 
  SDL_Surface* optimized_image = NULL; 
  loaded_image = IMG_Load(filename.c_str()); 
  try {
    if (loaded_image == NULL) { 
      throw 0;
    } 
    //Create an optimized image 
    optimized_image = SDL_DisplayFormat(loaded_image); 
    if (optimized_image == NULL) {
      throw 0;
    }
    //Free the old image 	
    SDL_FreeSurface(loaded_image); 
    //Return the optimized image 
    SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, color);
    return optimized_image; 
  } catch(int e) {
    char ch[100];
    sprintf(ch, "ERROR : %s",m_fn.c_str());
    MessageBoxA(NULL, 
                "Loading the image is failed , please sure that the file is there.",
                ch, MB_ICONERROR | MB_OK);
    SDL_Error(SDL_ENOMEM);
    SDL_Quit();
    std::exit(1);
  }
}
SDL_Rect GraphicsManager::InitRect(int x, int y, int width, int height) {
  SDL_Rect rec = {x, y, width, height};
  return rec;
}

int GraphicsManager::width_ = 0;
int GraphicsManager::height_ = 0;
SDL_Surface * GraphicsManager::screen_ = NULL;
bool GraphicsManager::fullscreen_ = false;
bool GraphicsManager::init_sdl_ = false;
int GraphicsManager::desk_height_ = 0;
int GraphicsManager::desk_width_ = 0;