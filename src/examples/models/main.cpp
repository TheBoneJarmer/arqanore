#include <arqanore/window.h>
#include <arqanore/keyboard.h>
#include <iostream>
#include "arqanore/exceptions.h"
#include "arqanore/model.h"
#include "arqanore/camera.h"
#include "arqanore/scene.h"
#include "arqanore/renderer.h"

arqanore::Model *model;
arqanore::Vector3 model_rot;

void on_open(arqanore::Window *window) {
    try {
        model = new arqanore::Model("assets/models/axis.arqm");
        model->calculate_normals(false);

        arqanore::Camera &cam = arqanore::Scene::cameras[0];
        cam.position.z = -10;
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_close(arqanore::Window *window) {
    delete model;
}

void on_update(arqanore::Window *window, double at) {
    try {
        if (arqanore::Keyboard::key_pressed(arqanore::Keys::ESCAPE)) {
            window->close();
        }

        model_rot.y++;
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_render2d(arqanore::Window *window) {
    try {

    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_render3d(arqanore::Window *window) {
    try {
        arqanore::Vector3 pos(0, 0, 0);
        arqanore::Quaternion rot = arqanore::Quaternion::rotate(arqanore::Quaternion(), model_rot);
        arqanore::Vector3 scale(1, 1, 1);

        arqanore::Renderer::render_model(window, model, pos, rot, scale, 0);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_opengl(arqanore::Window *window, std::string type, std::string severity, std::string message) {
    std::cout << "[" << type << "]" << "[" << severity << "] " << message << std::endl;
}

int main() {
    auto window = arqanore::Window(1440, 768, "Arqanore");
    window.on_open(on_open);
    window.on_close(on_close);
    window.on_update(on_update);
    window.on_render2d(on_render2d);
    window.on_render3d(on_render3d);
    //window.on_opengl(on_opengl);
    window.open(false, true, true);

    return 0;
}