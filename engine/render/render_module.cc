#include "render_module.h"
#include "../scene.h"
#include "../components/renderer.h"
#include "../resources/shader.h"
#include "../resources/material.h"
#include "../resources/mesh.h"
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace bellum {

void RenderModule::onStart(Scene* scene) {
  scene_ = scene;
}

void RenderModule::render() {
  render_state.clear();
  render_state.projection = Matrix4::makeOrthographic(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
  render_state.view_projection = render_state.projection;

  //glFrontFace(GL_CW);
  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ambientPass();
}

void RenderModule::ambientPass() {
  for (auto renderer : renderers_) {
    if (renderer->enabled()) {
      render_state.renderer = renderer;
      Material material = renderer->material();

      material.shader->bind();

      renderer->render();

      material.shader->release();
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }
}

void RenderModule::consolidate() {
  /*
  std::sort(std::begin(renderers_), std::end(renderers_), [](Renderer* a, Renderer* b) {
    return a->material().shader->pass_ - b->material().shader->pass_;
  });
  */
}

void RenderModule::addRenderer(Renderer* renderer) {
  renderers_.push_back(renderer);
}

}
