#include "application.h"
#include "standalone/standalone_application.h"

namespace bellum {

Application::Application() {}

Application* Application::getInstance() {
#ifdef BELLUM_STANDALONE
  static StandaloneApplication instance{};
  return &instance;
#endif
}

}
