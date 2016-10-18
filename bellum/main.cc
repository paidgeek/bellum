#include "bellum.h"
#include "main_scene.h"

using namespace bellum;

int main(int argc, const char* argv[]) {
  std::unique_ptr<Scene> awd(new MainScene{});
  //Application* application = Application::getInstance();
  //application->addScene(std::make_unique<MainScene>());
  //application->start(argc, argv);

  return 0;
}
