// breakout-main.cpp : Defines the entry point for the console application.

#include "breakout-main.h"

using namespace std;
using namespace breakout_debug;

SdlManager m;
bool keys[322] = {false};
// TODO: Game class that checks game status and holds vars like 'lives'
int lives = 3;
vector<Ball*> balls;
vector<Brick*> bricks;
bool quit;
Paddle player_paddle(0,0);
SDL_Surface* screen = NULL;
Object* obj_arr[WALL_HEIGHT * WALL_WIDTH];
unsigned int num_obj = 0;

int main(int argc, char* args[]) {
  // Intiialize random number
  std::srand(time(0));
  // Set up the screen
  GraphicsManager::initalizeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, false);
  screen = GraphicsManager::getScreen();
  // If there was an error in setting up the screen
  if(screen == NULL) { 
    return 1; 
  }
  SDL_WM_SetCaption("BreakOut", NULL );

  // TODO: Object Manager class
  // Initializing objects
  for (int y = 0; y < WALL_HEIGHT; ++y) {
    for (int x = 0; x < WALL_WIDTH; ++x) {
      bricks.push_back(new Brick(RED_BRICK, WALL_START_X + x * 32,
                                 WALL_START_Y + y * 32));
      obj_arr[num_obj] = bricks[x + y * WALL_WIDTH];
      num_obj++;
    }
  }
  player_paddle.set_x(GraphicsManager::GetScreenWidth() / 2);
  player_paddle.set_y(GraphicsManager::GetScreenHeight() - 32);
  balls.push_back(new Ball(BALL_SPEED, BALL_START_X,
                           BALL_START_Y, BALL_START_ANG));
  // TODO: Set the window's icon
  // Update the screen
  if(SDL_Flip(screen) == -1) { 
    return 1; 
  }
  Uint32 delay = 0;
  int time_start = SDL_GetTicks();
  int frames = 0;
  quit = false;
  while (!quit) {
    unsigned int sframe = SDL_GetTicks();
    ObjectManager::remove_dead();
    Draw();
    Logic();
    ++frames;
    // TODO: Changing framerate
    // Framerate handling
    int wait = ((float)1000/FRAMERATE) - (SDL_GetTicks() - sframe);
    if(wait > 0) {
      SDL_Delay(wait);
    }
  }
  int time_now = SDL_GetTicks();
  int time_over = (time_now - time_start);
  double frame_for_sec = ((double)frames / ((double)time_over/1000));
  DebugLine("frame rate:"+ breakout_debug::DoubleToStr(frame_for_sec) + 
            " frames:" + breakout_debug::IntToStr(frames) + 
            " for time (seconds):" + 
            breakout_debug::DoubleToStr((double)time_over/1000));
  SDL_Quit();
  return 0; 
}
void Logic() {
  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event)) {
    if (sdl_event.type == SDL_QUIT) {
      quit = true;
    }
    if (sdl_event.type == SDL_KEYDOWN) {
      if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
        quit = true;
      } else if (sdl_event.key.keysym.sym == SDLK_RIGHT) {
        player_paddle.IncreaseSpeed((float)(PADDLE_INC_SPEED),0);
      } else if (sdl_event.key.keysym.sym == SDLK_LEFT) {
        player_paddle.IncreaseSpeed((float)(-1 * PADDLE_INC_SPEED) ,0);
      } else if (sdl_event.key.keysym.sym == SDLK_F2) {
        GraphicsManager::initalizeScreen(SCREEN_WIDTH,SCREEN_HEIGHT,
                                          !(GraphicsManager::fullscreen_));
        screen = GraphicsManager::getScreen();
      }
      keys[sdl_event.key.keysym.sym] = true;
    }
    if (sdl_event.type == SDL_KEYUP) {
      if (sdl_event.key.keysym.sym == SDLK_RIGHT) {
        player_paddle.BreakSpeed();
      } else if (sdl_event.key.keysym.sym == SDLK_LEFT) {
        player_paddle.BreakSpeed();
      }
      keys[sdl_event.key.keysym.sym] = false;
    }
  }
  // If key already pressed
  HandleInput();
  // Movement
  for (unsigned int i=0; i<balls.size(); i++) {
    Ball *player = balls[i];
    if (player->get_y() >= GraphicsManager::GetScreenHeight()) {
      lives -= 1;
      player->set_x(50);
      player->set_y(50);
      player->set_speed(BALL_SPEED);
      player->set_angle(315.000);
      player_paddle.BreakSpeed();
      player_paddle.set_x(GraphicsManager::GetScreenWidth() / 2);
      player_paddle.set_y(GraphicsManager::GetScreenHeight() -32);
    }
    else 
    {
      if (CheckCollison(player->get_bounding_box(),
                        player_paddle.get_bounding_box())) {
        player->OnCollision(&player_paddle);
      }
      GridCollison(*player);
      player->Move();
      // DEPRECTED - check collison of the paddle with all the bricks
      // for(unsigned int j=0;j<(unsigned)num_obj;j++)
      //{
      //	if(!obj_arr[j]->IsDead() &&
      //CheckCollison(player->get_bounding_box(),obj_arr[j]->get_bounding_box()))
      //	{
      //		player->Bounce(obj_arr[j]->get_bounding_box(),TypeBrick);
      //		obj_arr[j]->Destroy();
      //		player->Move();
      //			
        //	}
      //}
      
      // Check collision of the powerup with the paddle
      for(Object* o : ObjectManager::get_objects())
      {
        if (o->IsDead()) continue;
        if (CheckCollison(player_paddle.get_bounding_box(),
                          o->get_bounding_box())) {
          player_paddle.OnCollision(o);
        }
      }
    }
  }
  player_paddle.Step();
}
void Draw() {
  SDL_Color back_col = {255, 255, 255, 0}; // White color
  ClearScreen(screen, back_col);
  for (unsigned int i = 0; i < balls.size(); i++) {
    Ball *player = balls[i];
    player->Draw();
  }
  player_paddle.Draw();
  for (unsigned int j = 0; j < num_obj; j++) {
    if (!obj_arr[j]->IsDead()) {
      obj_arr[j]->Draw();
    }
  }
  for (Object* o : ObjectManager::get_objects()) {
    o->Draw();
    o->Move();
  }
  // Update screen
  SDL_Flip(screen);
}
bool CheckCollison(SDL_Rect object, SDL_Rect target) {
  // Check rectangles collide
  if ((object.x + object.w) >= target.x && 
      object.x <= (target.x + target.w) && 
      (object.y + object.h) >= target.y && 
      object.y <= (target.y + target.h)) {
      return true;
  }
  return false;
}
bool GridCollison(Ball& obj) {
  SDL_Rect object = obj.get_bounding_box();
  // Check if the object at the bounds of the bricks
  if (object.x + object.w - WALL_START_X < 0 || 
      object.x > WALL_START_X + WALL_WIDTH * 32 || 
      object.y > WALL_START_Y + WALL_HEIGHT * 32 || 
      object.y + object.h < WALL_START_Y) {
      return false;
  } else {
    // Check all 4 corners
    int x_corners[2] = {0};
    int y_corners[2] = {0};
    x_corners[0] = object.x - WALL_START_X;
    x_corners[1] = x_corners[0] + object.w;
    y_corners[0] = object.y - WALL_START_Y;
    y_corners[1] = y_corners[0] + object.h;
    for (int i = 0; i < 2; ++i) {
      if (x_corners[i] < 0) {
        x_corners[i] = 0;
      }
      if (x_corners[i] >= 32 * WALL_WIDTH) {
        x_corners[i] = 32 * WALL_WIDTH - 1;
      }
      if (y_corners[i] < 0) {
        y_corners[i] = 0;
      }
      if (y_corners[i] >= 32 * WALL_HEIGHT) {
        y_corners[i] = 32 * WALL_HEIGHT - 1;
      }
    }
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        // Brick index in the wall
        int index = (x_corners[i] / 32) + (y_corners[j] / 32) * WALL_WIDTH;
        if (!obj_arr[index]->IsDead()) {
          obj.OnCollision(obj_arr[index]);
          obj_arr[index]->OnCollision(&obj);
          return true;
        }
      }
    }
    return false;
  }
}
void HandleInput() {
  if (keys[SDLK_F3]) {
    balls.push_back(new Ball(BALL_SPEED,30,30,-45));
  }
  if (keys[SDLK_ESCAPE]) {
    quit = true;
  }
  if (keys[SDLK_RIGHT]) {
    player_paddle.IncreaseSpeed((float)PADDLE_INC_SPEED, 0);
  }
  if (keys[SDLK_LEFT]) {
    player_paddle.IncreaseSpeed(-1 * (float)PADDLE_INC_SPEED, 0);
  }
}
// TODO: Move this to GraphicsManager
void ClearScreen(SDL_Surface* screen, SDL_Color color) {
  SDL_FillRect(screen, &screen->clip_rect, 
               SDL_MapRGB(screen->format, color.r, color.g, color.b));
}