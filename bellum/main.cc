#include "bellum.h"

using namespace bellum;

int main(int argc, char* argv[]) {
  Application* application = Application::getPlatformApplication();
  application->start(argc, argv);

  return 0;
}
