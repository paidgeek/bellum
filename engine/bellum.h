#ifndef BELLUM_BELLUM_H
#define BELLUM_BELLUM_H

#define APPLICATION_VERSION_MAJOR 1
#define APPLICATION_VERSION_MINOR 0
#define APPLICATION_VERSION_PATCH 0

#include "application.h"
#include "color.h"
#include "common.h"
#include "scene.h"
#include "node.h"
#include "component.h"
#include "random.h"
#include "input.h"
#include "timing.h"

// resources
#include "resources/binding_info.h"
#include "resources/material.h"
#include "resources/shader.h"
#include "resources/mesh.h"
#include "resources/attribute.h"
#include "resources/resource_loader.h"

// components
#include "components/mesh_filter.h"
#include "components/mesh_renderer.h"
#include "components/renderer.h"
#include "components/camera.h"

// math
#include "math/math.h"
#include "math/plane.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "math/quaternion.h"
#include "math/matrix4.h"

#endif
