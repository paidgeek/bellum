#ifndef BELLUM_LOGGER_H
#define BELLUM_LOGGER_H

#include <string>
#include <iostream>

namespace bellum {

class Logger {
public:
  Logger() {}

  Logger(std::string name)
    : name_(name) {}

  template<typename T, typename ...Args>
  void info(T&& msg, Args&& ... args) {
    std::cout << '[' << name_ << "]: ";
    printHelper(std::cout, msg, std::forward<Args>(args)...);
  }

  template<typename T>
  void info(T&& msg) {
    std::cout << '[' << name_ << "]: " << msg << std::endl;
  }

  template<typename T, typename ...Args>
  void error(T&& msg, Args&& ... args) {
    std::cerr << '[' << name_ << "]: ";
    printHelper(std::cerr, msg, std::forward<Args>(args)...);
  }

  template<typename T>
  void error(T&& msg) {
    std::cerr << '[' << name_ << "]: " << msg << std::endl;
  }

private:
  std::string name_;

  void printHelper(std::ostream& out) {
    out << std::endl;
  }

  template<typename T, typename... Args>
  void printHelper(std::ostream& out, T&& msg, Args&& ...args) {
    out << std::forward<T>(msg);
    printHelper(out, std::forward<Args>(args)...);
  }
};

}

#endif
