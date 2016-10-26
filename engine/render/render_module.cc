#include "render_module.h"
#include "../scene.h"
#include "../components/renderer.h"
#include "../resources/shader.h"
#include "../resources/mesh.h"
#include <GL/glew.h>
#include "../components/camera.h"
#include "../timing.h"

namespace bellum {

void RenderModule::onStart(Scene* scene) {
  scene_ = scene;
}

void RenderModule::render() {
  Camera* camera = Camera::current();
  Color clearColor = camera->clearColor();
  Matrix4 view = camera->view();
  Matrix4 projection = camera->projection();

  render_state.clear();
  render_state.projection = projection;
  render_state.view_projection = projection * view;

  //glFrontFace(GL_CW);
  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  switch (camera->clearFlags()) {
    case Camera::ClearFlags::NOTHING:
      break;
    case Camera::ClearFlags::DEPTH:
      glClear(GL_DEPTH_BUFFER_BIT);
      break;
    case Camera::ClearFlags::SOLID_COLOR:
      glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      break;
  }

  ambientPass();
}

void RenderModule::ambientPass() {
  for (auto renderer : renderers_) {
    if (renderer->enabled()) {
      render_state.renderer = renderer;
      Material material = renderer->material();

      material.shader->bind();
      Matrix4 model = renderer->node()->transform().localToWorld();
      Matrix4 mvp = render_state.view_projection * model;

      material.shader->setUniform("MVP", render_state.view_projection);

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
