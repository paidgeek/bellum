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

void StandaloneApplication::start(std::vector<std::string> args) {
  logger_ = std::make_unique<Logger>("Bellum");

  int32 width = 480;
  int32 height = 360;
  bool vsync = false;
  double targetUps = 60.0;
  {
    // parse '--x=y' arguments
    std::stringstream ss;

    for(const auto& arg : args) {
      if (arg.compare(0, 8, "--width=") == 0) {
        ss.str(arg.substr(8));
        ss >> width;
      } else if (arg.compare(0, 9, "--height=") == 0) {
        ss.str(arg.substr(9));
        ss >> height;
      } else {
        logger_->error("Unknown option '", arg, "'");
        continue;
      }

      if (ss.fail() || ss.get() != -1) {
        logger_->error("Failed to parse '", arg, "', using defaults");
      }

      ss.clear();
    }
  }

  double frameTime = 1.0 / targetUps;
  Time::setDeltaTime(static_cast<float>(frameTime));
  double currentTime;
  double previousTime = Time::currentSeconds();
  double elapsed;
  double lag = 0.0;
  float lagOffset = 0.0f;
  double lastFpsUpdate = 0.0;
  int framesProcessed = 0;

  window_ = std::make_unique<Window>(width, height);

  logger_->info("Application started");
  srand((uint32) Time::currentNanoseconds());
  running_ = true;

  try {
    window_->show();
    super::onStart();

    while (running_ && !window_->shouldClose()) {
      currentTime = Time::currentSeconds();
      elapsed = currentTime - previousTime;

      // update
      lag += elapsed;
      while (lag > frameTime) {
        super::update();
        window_->update();
        lag -= frameTime;
      }

      // render
      lagOffset = static_cast<float>(lag / frameTime);
      super::render();

      framesProcessed++;
      if (currentTime - lastFpsUpdate >= 1.0) {
        Time::setFps(framesProcessed);
        framesProcessed = 0;
      }

      window_->render();
      previousTime = currentTime;
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
