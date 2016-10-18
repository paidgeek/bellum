#include "application.h"
#include "standalone/standalone_application.h"

INITIALIZE_EASYLOGGINGPP

namespace bellum {

Application* Application::getPlatformApplication() {
#ifdef BELLUM_STANDALONE
  return new StandaloneApplication{};
#endif
}

}
