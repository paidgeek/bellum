#include "standalone_application.h"

namespace bellum {

StandaloneApplication::StandaloneApplication()
  : logger_(Logger::getLogger("Bellum")) {}

void StandaloneApplication::start(int argc, char* argv[]) {
  window_ = std::make_shared<Window>(1280, 720);

  try {
    window_->show();
  } catch (const std::exception& e) {
    logger_->error(e.what());
    std::terminate();
  }

  logger_->info("Application started");
}

void StandaloneApplication::exit() {
  logger_->info("Application exited");
}

}
