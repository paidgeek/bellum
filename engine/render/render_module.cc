#include "render_module.h"
#include "../scene.h"
#include "../components/renderer.h"
#include "../resources/shader.h"
#include "../resources/mesh.h"
#include <GL/glew.h>
#include "../components/camera.h"

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
      GL_CHECK();
      //Matrix4 model = renderer->node()->transform().localToWorld();
      //Matrix4 mvp = render_state.view_projection * model;

     // Matrix4 proj = Matrix4::makePerspective(60, 16.0f / 9.0f, 0.01f, 100.0f);
      Matrix4 proj = Matrix4::makeOrthographic(0, 1, 0, 1, -1, 1);
      Matrix4 model = Matrix4::makeTranslation(0, 0, 5);

      material.shader->setUniform("MVP", Matrix4::identity());
      GL_CHECK();

      renderer->render();
      GL_CHECK();

      material.shader->release();
      GL_CHECK();
      //glActiveTexture(GL_TEXTURE0);
      //glBindTexture(GL_TEXTURE_2D, 0);
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
