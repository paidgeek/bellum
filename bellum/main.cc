#include "bellum.h"
#include "main_scene.h"

using namespace bellum;

int main(int argc, const char* argv[]) {
  Application* application = Application::getInstance();
  application->addScene("Main", std::make_unique<MainScene>());
  application->start(argc, argv);

  return 0;
}
