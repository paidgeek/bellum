#include <ctime>
#include "bellum.h"
#include "main_scene.h"

using namespace bellum;

int main(int argc, const char* argv[]) {
  //std::cout << Matrix4::makeTransformation({1, 2, 3}, Quaternion::makeAngleAxis(Math::rad(60), {1,0,0}), {2,4,8}) << std::endl;

  Application* application = Application::instance();
  application->addScene("Main", std::make_unique<MainScene>());
  application->start(argc, argv);

  return 0;
}
