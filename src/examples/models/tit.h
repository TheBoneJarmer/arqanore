#pragma once

#include "arqanore/vector3.h"
#include "arqanore/window.h"
#include "arqanore/collider.h"
#include "arqanore/rigidbody.h"
#include "arqanore/light.h"

class Tit {
private:
    arqanore::Vector3 position;
    arqanore::Quaternion rotation;
    arqanore::RigidBody body;
    bool disposed;

    void init_body();

    void update_body(double at);

public:
    bool is_disposed();

    Tit();

    void update(double at);

    void render(arqanore::Window *window);

    void dispose();

    void jump();
};