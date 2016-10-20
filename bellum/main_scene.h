#ifndef __BELLUM_MAIN_SCENE_H__
#define __BELLUM_MAIN_SCENE_H__

#include <bellum.h>
#include "test_component.h"

using namespace bellum;

class MainScene : public Scene {
public:
  MainScene() {}

  void make() override {
    Node* test = makeNode();
    Component* comp = makeComponent<TestComponent>(test);
  }

};

#endif
