#include "bellum.h"
#include "main_scene.h"

using namespace bellum;

int main(int argc, const char* argv[]) {
  std::cout << argv[0] << std::endl;

  Application* application = Application::getInstance();
  application->addScene("Main", std::make_unique<MainScene>());
  application->start(argc, argv);

  return 0;
}
