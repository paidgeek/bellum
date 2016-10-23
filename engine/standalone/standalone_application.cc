#include <cstdlib>
#include <sstream>
#include <cstring>
#include "resources/resource_loader.h"
#include "standalone_application.h"
#include "window.h"
#include "../timing.h"

namespace bellum {

StandaloneApplication::StandaloneApplication() : super::Application() {}

StandaloneApplication::~StandaloneApplication() {}

void StandaloneApplication::start(int argc, const char* argv[]) {
  logger_ = std::make_unique<Logger>("Bellum");

  int32 width = 480;
  int32 height = 360;
  bool vsync = false;
  double targetUps = 60.0;
  {
    // parse '--x=y' arguments
    std::stringstream ss;

    for (int32 i = 1; i < argc; i++) {
      if (std::strncmp("--width=", argv[i], 8) == 0) {
        ss.str(argv[i] + 8);
        ss >> width;
      } else if (std::strncmp("--height=", argv[i], 9) == 0) {
        ss.str(argv[i] + 9);
        ss >> height;
      } else {
        logger_->error("Unknown option '", argv[i], "'");
        continue;
      }

      if (ss.fail() || ss.get() != -1) {
        logger_->error("Failed to parse '", argv[i], "', using defaults");
      }

      ss.clear();
    }
  }

  FixedTimeStepTimer frameTimer{targetUps};
  frameTimer.start();

  window_ = std::make_unique<Window>(width, height);

  logger_->info("Application started");
  running_ = true;

  try {
    window_->show();
    super::onStart();

    while (running_ && !window_->shouldClose()) {
      frameTimer.update();

      // update
      while (frameTimer.doUpdate()) {
        super::update();
      }

      // render
      frameTimer.doRender();
      super::render();
      window_->render();
    }
  } catch (const std::exception& e) {
    logger_->error(e.what());
  }

  ResourceLoader::disposeAll();
  logger_->info("Application exited");
}

void StandaloneApplication::exit() {
  running_ = false;
}

}
