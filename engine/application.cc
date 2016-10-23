#include "application.h"
#include "standalone/standalone_application.h"
#include "scene_manager.h"
#include "scene.h"

namespace bellum {

Application::Application()
  : update_module_(std::make_unique<UpdateModule>()),
    render_module_(std::make_unique<RenderModule>()) {}

Application* Application::getInstance() {
#ifdef BELLUM_STANDALONE
  static StandaloneApplication instance{};
  return &instance;
#endif
}

void Application::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
  SceneManager::addScene(name, std::move(scene));
}

void Application::onStart() {
  Scene* currentScene = SceneManager::currentScene();

  update_module_->onStart(currentScene);
  render_module_->onStart(currentScene);

  currentScene->make();
}

void Application::update() {
  update_module_->update();
  render_module_->update();
}

void Application::render() {
  update_module_->render();
  render_module_->render();
}

}
