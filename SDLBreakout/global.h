#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include "define.h"
#include "debug.h"
#include "graphics-manager.h"
#include "sdl-manager.h"

enum BrickType {PURPLE_BRICK, RED_BRICK};
enum ObjectType {TYPE_PADDLE , TYPE_BRICK, TYPE_BALL, TYPE_POWERUP};
enum PowerType { TYPE_PWR_PADDLE_UP, TYPE_PWR_PADDLE_DOWN };