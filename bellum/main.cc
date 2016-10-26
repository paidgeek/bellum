#include <ctime>
#include "bellum.h"
#include "main_scene.h"
#include <chrono>

using namespace bellum;

int main(int argc, const char* argv[]) {
  Application* application = Application::instance();
  application->addScene("Main", std::make_unique<MainScene>());
  application->start(argc, argv);

  return 0;
}
