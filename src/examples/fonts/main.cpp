#include <iostream>
#include "arqanore/window.h"
#include "arqanore/keyboard.h"
#include "arqanore/renderer.h"
#include "arqanore/font.h"
#include "arqanore/exceptions.h"

arqanore::Font *font;

void on_open(arqanore::Window *window) {
    try {
        font = new arqanore::Font("assets/fonts/arial.ttf", 20, 20);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while loading assets" << std::endl;
    }
}

void on_close(arqanore::Window *window) {
    delete font;
}

void on_update(arqanore::Window *window, double at) {
    if (arqanore::Keyboard::key_pressed(arqanore::Keys::ESCAPE)) {
        window->close();
    }
}

void render_text(arqanore::Window *window) {
    auto text = "Hello, this is a !rgb(0,255,0)normal piece of text! This text will continue to be rendered to the right even if it leaves the screen at some point.";

    arqanore::Renderer::render_text(window, font, text, arqanore::Vector2(32, 32), arqanore::Color::WHITE);
}

void render_paragraph(arqanore::Window *window) {
    auto text = "But this is a parapraph of words. Words are separated by spaces and therefore the renderer does the same. "
                "But not just only that! It also makes sure to enter a new line when a word would reach out of boundaries.\n \n "
                "On top of that there is also some hidden features! Like newlines for example. And\tadding\ttabs too! "
                "And is not the only thing! It is possible to use !rgba(35,35,185,255)colors as well!";

    arqanore::Renderer::render_paragraph(window, font, text, arqanore::Vector2(32, 64), window->get_width() - 64, arqanore::Color::WHITE);
}

void on_render_2d(arqanore::Window *window) {
    try {
        render_text(window);
        render_paragraph(window);
    } catch (arqanore::ArqanoreException &ex) {
        std::cerr << ex.what() << std::endl;
        window->close();
    } catch (...) {
        std::cerr << "An unknown error occurred while rendering" << std::endl;
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
    window.on_render2d(on_render_2d);
    window.on_opengl(on_opengl);
    window.open(false, true);

    return 0;
}
