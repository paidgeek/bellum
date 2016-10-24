#include "renderer.h"
#include "../application.h"
#include "../render/render_module.h"

namespace bellum {

void Renderer::setMaterial(const Material& material)  {
  material_ = material;
  Application::instance()->render_module_->consolidate();
}

}
