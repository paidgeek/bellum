#ifndef BELLUM_LOGGER_H
#define BELLUM_LOGGER_H

#include "easylogging++.h"

namespace bellum {

class Logger {
public:
  static Logger getLogger(const char* name) {
    return Logger{el::Loggers::getLogger(name)};
  }

  el::Logger* operator->() {
    return logger_;
  }
private:
  Logger(el::Logger* logger)
    : logger_(logger) {}

  el::Logger* logger_;
};

}

#endif
