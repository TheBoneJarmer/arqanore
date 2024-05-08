#include <iostream>
#include <arqanore/window.h>
#include "arqanore/keyboard.h"
#include "arqanore/sprite.h"
#include "arqanore/renderer.h"
#include "arqanore/exceptions.h"

arqanore::Sprite *sprite;
arqanore::Vector2 position;
arqanore::Vector2 scale;

int frame_hor;
int frame_vert;
int frame_time;

void on_open(arqanore::Window *window) {
    try {
        sprite = new arqanore::Sprite("assets/sprites/cavern.png", 16, 16);

        position = arqanore::Vector2(64, 64);
        scale = arqanore::Vector2(16, 16);

        frame_hor = 0;
        frame_time = 0;
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_close(arqanore::Window *window) {
    delete sprite;
}

void on_update(arqanore::Window *window, double at) {
    if (arqanore::Keyboard::key_pressed(arqanore::Keys::ESCAPE)) {
        window->close();
    }

    if (frame_time < 16) {
        frame_time++;
    } else {
        frame_time = 0;
        frame_hor++;
    }

    if (frame_hor == sprite->get_frames_hor()) {
        frame_hor = 0;
        frame_vert++;
    }

    if (frame_vert == sprite->get_frames_vert()) {
        frame_vert = 0;
    }
}

void on_render_2d(arqanore::Window *window) {
    try {
        arqanore::Renderer::render_sprite(window, sprite, position, scale, arqanore::Vector2::ZERO, 0, frame_hor, frame_vert, false, false, arqanore::Color::WHITE);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    }
}

void on_opengl(arqanore::Window *window, std::string type, std::string severity, std::string message) {
    std::cout << "[" << type << "]" << "[" << severity << "] " << message << std::endl;
}

int main() {
    auto window = arqanore::Window(1440, 768, "Arqanore - Sprites");
    window.on_open(on_open);
    window.on_close(on_close);
    window.on_update(on_update);
    window.on_render2d(on_render_2d);
    window.on_opengl(on_opengl);
    window.open(false, true, true);

    return 0;
}