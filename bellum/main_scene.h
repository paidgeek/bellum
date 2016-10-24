#ifndef __BELLUM_MAIN_SCENE_H__
#define __BELLUM_MAIN_SCENE_H__

#include "bellum.h"
#include "test_component.h"
#include "fly_camera.h"

using namespace bellum;

class MainScene : public Scene {
public:
  void make() override {
    {
      // camera
      Node* camNode = Node::make();
      Camera* camera = camNode->addComponent<Camera>();
      camera->setProjection(Matrix4::makePerspective(60.0f, 16.0f / 9.0f, 0.01f, 100.0f));

      //camNode->addComponent<FlyCamera>();

      Camera::setCurrent(camera);
    }

    Node* test = Node::make();
    TestComponent* comp = test->addComponent<TestComponent>();
    MeshFilter* mf = test->addComponent<MeshFilter>();

    Mesh* mesh = ResourceLoader::makeEmptyMesh(BindingInfo{
      AttributeKind::POSITION, AttributeKind::COLOR
    });

    {
      mesh->setVertices({
                          {0.0f, 0.0f, 0.0f},
                          {1.0f, 0.0f, 0.0f},
                          {1.0f, 1.0f, 0.0f}
                        });
      mesh->setColors({
        Color::red(),
        Color::green(),
        Color::blue()
                      });
      mesh->setTriangles({0, 1, 2});
      mesh->uploadMeshData(true);
    }

    mf->setMesh(mesh);

    MeshRenderer* mr = test->addComponent<MeshRenderer>();
    mr->setMaterial({
                      ResourceLoader::loadShader("shaders/vertex_color.vs",
                                                 "shaders/vertex_color.fs",
                                                 BindingInfo{
                                                   AttributeKind::POSITION,
                                                   AttributeKind::COLOR
                                                 }, {"MVP"})
                    });

    MeshRenderer mr2 = *mr;
  }

};

#endif
