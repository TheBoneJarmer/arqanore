#include "tit.h"
#include "arqanore/renderer.h"
#include "game_assets.h"
#include "arqanore/mathhelper.h"
#include "arqanore/shaders.h"
#include "arqanore/scene.h"

void Tit::init_body() {
    arqanore::BoxCollider collider(2, 2, 2);

    this->body = arqanore::RigidBody(0);
    this->body.add_collider(collider);
    this->body.position(this->position);
    this->body.rotation(this->rotation);
}

void Tit::update_body(double at) {
    this->body.update(at);
    this->position = body.position();
    this->rotation = body.rotation();

    if (this->body.sleeping()) {
        this->jump();
    }

    if (this->position.y < -100) {
        this->dispose();
    }
}

bool Tit::is_disposed() {
    return disposed;
}

Tit::Tit() {
    float x = -10 + (rand() % 20);
    float z = -10 + (rand() % 20);

    this->disposed = false;
    this->position = arqanore::Vector3(x * 4, 50, z * 4);
    this->rotation = arqanore::Quaternion();

    init_body();
}

void Tit::update(double at) {
    update_body(at);
}

void Tit::render(arqanore::Window *window) {
    if (disposed) {
        return;
    }

    arqanore::Renderer::render_model(window, GameAssets::model_tit, position, rotation, arqanore::Vector3::ONE, 0);
}

void Tit::dispose() {
    if (this->disposed) {
        return;
    }

    this->body.dispose();
    this->disposed = true;
}

void Tit::jump() {
    int factor = rand() % 1000;

    arqanore::Vector3 force;
    force.y = 1000;
    force.x = -500 + factor;
    force.z = -500 + factor;

    this->body.apply_force(force);
}
