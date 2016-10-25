#include <cstdlib>
#include <sstream>
#include <cstring>
#include "resources/resource_loader.h"
#include "standalone_application.h"
#include "window.h"
#include "../timing.h"
#include "resources/mesh.h"
#include "color.h"
#include "resources/shader.h"
#include <Gl/glew.h>

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
      if(currentTime - lastFpsUpdate >= 1.0) {
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
