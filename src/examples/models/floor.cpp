#include "floor.h"
#include "arqanore/vector3.h"
#include "arqanore/renderer.h"
#include "game_assets.h"

Floor::Floor(float x, float z) {
    float y = rand() % 20;

    collider = arqanore::BoxCollider(4.79f, 1.31f, 4.79);
    body = arqanore::RigidBody(1);
    body.add_collider(collider);
    body.position(arqanore::Vector3(x, -10 + y, z));
}

void Floor::update(double at) {
    body.update(at);

    this->position = body.position();
    this->rotation = body.rotation();
}

void Floor::render(arqanore::Window *window) {
    arqanore::Vector3 scale = arqanore::Vector3::ONE;

    try {
        arqanore::Renderer::render_model(window, GameAssets::model_floor, position, rotation, scale, 0);
    } catch (arqanore::ArqanoreException& ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}
