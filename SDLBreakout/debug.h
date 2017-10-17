#pragma once
#include "global.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

namespace breakout_debug {

std::string GetTimeNow();
void DebugLine(string line);
void PrintDebug();
std::string IntToStr(int i);
std::string DoubleToStr(double d);

extern ostringstream debug_str;
extern ofstream d_file;
}