#ifndef __BELLUM_FMT_H__
#define __BELLUM_FMT_H__

#include <string>
#include <sstream>

namespace bellum {

class Formatter {
public:
  template<typename T, typename ...Args>
  static std::string str(T&& msg, Args&& ... args) {
    std::stringstream ss;
    fmtHelper(ss, msg, std::forward<Args>(args)...);
    return ss.str();
  }

private:
  static void fmtHelper(std::stringstream& ss) {
    ss << std::endl;
  }

  template<typename T, typename... Args>
  static void fmtHelper(std::stringstream& ss, T&& msg, Args&& ...args) {
    ss << std::forward<T>(msg);
    fmtHelper(ss, std::forward<Args>(args)...);
  }
};

}

#endif
