#pragma once
#include "global.h"
#include "Ball.h"
#include "brick.h"
#include "Paddle.h"

bool CheckCollison(SDL_Rect object,SDL_Rect target);
bool GridCollison(Ball &obj);
void ClearScreen(SDL_Surface* screen,SDL_Color color);
void HandleInput();
void Draw();
void Logic();

