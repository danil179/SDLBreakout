#include "debug.h"

namespace breakout_debug {

string breakout_debug::GetTimeNow() {
  struct tm now;
  ostringstream s1;
  time_t t = time(0); // get time
  localtime_s(&now, &t);
  s1 << (now.tm_year + 1900) << '-' << (now.tm_mon + 1) << '-' << now.tm_mday 
     << " " << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec;
  return s1.str();
}
void breakout_debug::DebugLine(string line) {
  debug_str.str("");
  debug_str.clear();
  debug_str << line << endl;
  PrintDebug();
}
void breakout_debug::PrintDebug() {
  d_file.setf(ios::app | ios::out);
  d_file << debug_str.str();
}
std::string breakout_debug::IntToStr(int i) {
  ostringstream ss;
  ss << i;
  return ss.str();
}
std::string breakout_debug::DoubleToStr(double d) {
  ostringstream ss;
  ss << d;
  return ss.str();
}

ostringstream debug_str("");
ofstream d_file("../"+LOG_FOLDER+"/"+LOG_FILENAME,ios::out);
}