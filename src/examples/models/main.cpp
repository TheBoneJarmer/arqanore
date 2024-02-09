#include <arqanore/window.h>
#include <arqanore/keyboard.h>
#include <iostream>
#include "arqanore/renderer.h"
#include "game_assets.h"
#include "game_scene.h"

void on_open(arqanore::Window *window) {
    try {
        GameAssets::load(window);
        GameScene::init();
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_close(arqanore::Window *window) {
    GameAssets::dispose();
}

void on_tick(arqanore::Window *window, double dt) {
    try {
        GameScene::tick(window, dt);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_update(arqanore::Window *window, double at) {
    try {
        if (arqanore::Keyboard::key_pressed(arqanore::Keys::ESCAPE)) {
            window->close();
        }

        GameScene::update(window, at);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_render2d(arqanore::Window *window) {
    try {
        GameScene::render2D(window);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_render3d(arqanore::Window *window) {
    try {
        GameScene::render3D(window);
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

    try {

        window.on_open(on_open);
        window.on_close(on_close);
        window.on_tick(on_tick);
        window.on_update(on_update);
        window.on_render2d(on_render2d);
        window.on_render3d(on_render3d);
        window.on_opengl(on_opengl);
        window.open(false, true);
    } catch (arqanore::ArqanoreException &ex) {
        window.close();
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}