#include "application.h"
#include "standalone/standalone_application.h"
#include "update/update_module.h"
#include "render/render_module.h"
#include "scene_manager.h"
#include "scene.h"

namespace bellum {

Application::Application()
  : scene_manager_(std::make_unique<SceneManager>()),
    update_module_(std::make_unique<UpdateModule>()),
    render_module_(std::make_unique<RenderModule>()) {}

Application* Application::getInstance() {
#ifdef BELLUM_STANDALONE
  static StandaloneApplication instance{};
  return &instance;
#endif
}

void Application::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
  scene_manager_->addScene(name, std::move(scene));
}

void Application::onStart() {
  Scene* currentScene = scene_manager_->currentScene();
  currentScene->make();

  update_module_->onEnterScene(currentScene);
  render_module_->onEnterScene(currentScene);
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
