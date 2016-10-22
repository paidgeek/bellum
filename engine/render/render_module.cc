#include "render_module.h"
#include "../scene.h"
#include "../component.h"
#include "../components/renderer.h"

#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bellum {

void RenderModule::onEnterScene(Scene* scene) {
  scene_ = scene;
  scene_->registerOnAddComponent([this](Component* component) {
    this->onAddComponent(component);
  });
  scene_->registerOnRemoveComponent([this](Component* component) {
    this->onRemoveComponent(component);
  });
}

void RenderModule::render() {
  render_state.clear();
  render_state.projection = Matrix4::makeOrthographic(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
  render_state.view_projection = render_state.projection;

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ambientPass();
}

void RenderModule::ambientPass() {
  for (auto renderer : renderers_) {
    if (renderer->enabled()) {
      render_state.renderer = renderer;

      glActiveTextureARB(GL_TEXTURE0_ARB);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
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
