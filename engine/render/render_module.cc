#include "render_module.h"
#include "../scene.h"
#include "../components/renderer.h"
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bellum {

void RenderModule::onEnterScene(Scene* scene) {
  scene_ = scene;
  scene_->registerOnAddComponent(this->onAddComponent);
  scene_->registerOnRemoveComponent(this->onRemoveComponent);
}

void RenderModule::render() {
  render_state.clear();
  Matrix4::makeOrthographic(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f, render_state.projection);
  render_state.view_projection = render_state.projection;

  ambientPass();
}

void RenderModule::ambientPass() {
  for(auto renderer : renderers_) {

  }
}

void RenderModule::onAddComponent(Component* component) {
  Renderer* renderer = dynamic_cast<Renderer*>(component);
  if (renderer != nullptr) {
    renderers_.push_back(renderer);
  }
}

void RenderModule::onRemoveComponent(Component* component) {
  Renderer* renderer = dynamic_cast<Renderer*>(component);

  if (renderer != nullptr) {
    auto i = std::find(std::begin(renderers_), std::end(renderers_), renderer);

    if (i != renderers_.end()) {
      renderers_.erase(i);
    } else {
      throw IllegalRenderersState{};
    }
  }
}

}
