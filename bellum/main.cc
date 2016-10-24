#include <ctime>
#include "bellum.h"
#include "main_scene.h"
#include <chrono>

using namespace bellum;

int main(int argc, const char* argv[]) {
  /*
  Matrix4 m1 = Matrix4::makePerspective(60.0f, 16.0f / 9.0f, 0.01f, 100.0f);
  Matrix4 m2 = Matrix4::makeTransformation({1, -1, 2}, Quaternion::makeEuler(30, -30, 60), {2, 4, 8});
*/
  //std::cout << Quaternion::makeEuler(30, -30, 60) << std::endl;
  //std::cout << m1 << std::endl;
  //std::cout << m2 << std::endl;
  //std::cout << m1 * m2 << std::endl;
  Application* application = Application::instance();
  application->addScene("Main", std::make_unique<MainScene>());
  application->start(argc, argv);

  return 0;
}
