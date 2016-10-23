#ifndef __BELLUM_TEST_COMPONENT_H__
#define __BELLUM_TEST_COMPONENT_H__

#include "bellum.h"
using namespace bellum;

class TestComponent : public Component {
public:

  virtual void onAdd() override {
    Application::getInstance()->logger()->info("on add");
  }

  virtual void onRemove() override {
    Application::getInstance()->logger()->info("on remove");
  }

  virtual void onEnable() override {
    Application::getInstance()->logger()->info("on enable");
  }

  virtual void onDisable() override {
    Application::getInstance()->logger()->info("on disable");
  }

  virtual void update() override {
    //Application::getInstance()->logger()->info("update");
  }

};

#endif
