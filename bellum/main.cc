#include <ctime>
#include "bellum.h"
#include "main_scene.h"

using namespace bellum;

int main(int argc, char* argv[]) {
  Application* application = Application::instance();
  application->addScene("Main", std::make_unique<MainScene>());
  application->start({argv + 1, argv + argc});

  return 0;
}
