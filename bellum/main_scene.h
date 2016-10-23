#ifndef __BELLUM_MAIN_SCENE_H__
#define __BELLUM_MAIN_SCENE_H__

#include "bellum.h"
#include "test_component.h"

using namespace bellum;

class MainScene : public Scene {
public:
  void make() override {
    Node* test = Node::make();
    TestComponent* comp = test->addComponent<TestComponent>();
    MeshFilter* mf = test->addComponent<MeshFilter>();

    Mesh* mesh = ResourceLoader::makeEmptyMesh(BindingInfo{
      AttributeKind::POSITION, AttributeKind::COLOR
    });
    mesh->setVertices({
                        Vector3{0.0f, 0.0f, 0.0f},
                        Vector3{1.0f, 0.0f, 0.0f},
                        Vector3{1.0f, 1.0f, 0.0f}
                      });
    mesh->setColors({
                      Color::red(),
                      Color::green(),
                      Color::blue(),
                    });
    mf->setMesh(mesh);

    MeshRenderer* mr = test->addComponent<MeshRenderer>();
    mr->setMaterial({
                      ResourceLoader::loadShader("shaders/vertex_color.vs",
                                                 "shaders/vertex_color.fs",
                                                 BindingInfo{
                                                   AttributeKind::POSITION,
                                                   AttributeKind::COLOR
                                                 })
                    });

    MeshRenderer mr2 = *mr;
  }

};

#endif
