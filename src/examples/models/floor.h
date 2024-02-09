#pragma once

#include "arqanore/window.h"
#include "arqanore/vector3.h"
#include "arqanore/collider.h"
#include "arqanore/rigidbody.h"

class Floor {
private:
    arqanore::BoxCollider collider;
    arqanore::RigidBody body;

public:
    arqanore::Vector3 position;
    arqanore::Quaternion rotation;

    Floor(float x, float z);

    void update(double at);

    void render(arqanore::Window* window);
};