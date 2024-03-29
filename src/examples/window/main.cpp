#include <arqanore/window.h>
#include <arqanore/keyboard.h>
#include <iostream>

void on_open(arqanore::Window *window) {

}

void on_close(arqanore::Window *window) {

}

void on_update(arqanore::Window *window, double at) {
    if (arqanore::Keyboard::key_pressed(arqanore::Keys::ESCAPE)) {
        window->close();
    }
}

void on_render2d(arqanore::Window *window) {

}

void on_render3d(arqanore::Window *window) {

}

void on_opengl(arqanore::Window* window, std::string type, std::string severity, std::string message) {
    std::cout << "[" << type << "]" << "[" << severity << "] " << message << std::endl;
}

int main() {
    auto window = arqanore::Window(1440, 768, "Arqanore");
    window.on_open(on_open);
    window.on_close(on_close);
    window.on_update(on_update);
    window.on_render2d(on_render2d);
    window.on_render3d(on_render3d);
    window.on_opengl(on_opengl);
    window.open(false, true);

    return 0;
}