#pragma once
#include "global.h"

#define PI 3.14159
#define rad_to_deg(rad) (rad *  (180/PI))
#define deg_to_rad(deg) (deg * (PI / 180))

#define SCREEN_BPP 32
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// TODO: Change some of these defines to consts
#define BALL_START_X 50
#define BALL_START_Y 50
#define BALL_START_ANG 315
#define BALL_SPEED 300
#define BALL_PADDLE_ANGLE_LEFT 135

#define PADDLE_INC_SPEED 10

#define FRAMERATE 120

#define WALL_WIDTH 20
#define WALL_HEIGHT 20
#define WALL_START_X 100
#define WALL_START_Y 10

//#define DEBUG_DRAW 1
//#define DEBUG_SPEED 1

const std::string IMAGES_FOLDER = "Resources";
const std::string LOG_FOLDER = "Resources";
const std::string LOG_FILENAME = "log.txt";