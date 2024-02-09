#include <iostream>
#include "glad/gl.h"
#include "arqanore/window.h"
#include "arqanore/keyboard.h"
#include "arqanore/mouse.h"
#include "arqanore/audio.h"
#include "arqanore/exceptions.h"
#include "arqanore/shaders.h"
#include "arqanore/renderer.h"
#include "arqanore/physics.h"
#include "arqanore/scene.h"

void arqanore::Window::opengl_debug_callback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char *message, const void *user_param) {
    auto win = (Window *) user_param;
    auto str_type = std::to_string(type);
    auto str_severity = std::to_string(severity);
    auto str_message = std::string(message);

    if (type == GL_DEBUG_TYPE_ERROR) str_type = "ERROR";
    if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) str_type = "DEPRECATED_BEHAVIOR";
    if (type == GL_DEBUG_TYPE_MARKER) str_type = "MARKER";
    if (type == GL_DEBUG_TYPE_OTHER) str_type = "OTHER";
    if (type == GL_DEBUG_TYPE_PERFORMANCE) str_type = "PERFORMANCE";
    if (type == GL_DEBUG_TYPE_POP_GROUP) str_type = "POP_GROUP";
    if (type == GL_DEBUG_TYPE_PORTABILITY) str_type = "PORTABILITY";
    if (type == GL_DEBUG_TYPE_PUSH_GROUP) str_type = "PUSH_GROUP";
    if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) str_type = "UNDEFINED_BEHAVIOR";

    if (severity == GL_DEBUG_SEVERITY_HIGH) str_severity = "HIGH";
    if (severity == GL_DEBUG_SEVERITY_LOW) str_severity = "LOW";
    if (severity == GL_DEBUG_SEVERITY_MEDIUM) str_severity = "MEDIUM";
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) str_severity = "NOTIFICATION";

    if (win->window_opengl_cb != nullptr) {
        win->window_opengl_cb(win, str_type, str_severity, str_message);
    }
}

void arqanore::Window::error_callback(int error_code, const char *error_description) {
    throw new arqanore::GlfwException(error_code, error_description);
}

void arqanore::Window::window_resize_callback(GLFWwindow *handle, int width, int height) {
    auto win = (Window *) glfwGetWindowUserPointer(handle);

    if (win->window_resize_cb != nullptr) {
        win->window_resize_cb(win, width, height);
    }

    win->width = width;
    win->height = height;
}

void arqanore::Window::window_pos_callback(GLFWwindow *handle, int x, int y) {
    auto win = (Window *) glfwGetWindowUserPointer(handle);

    if (win->window_pos_cb != nullptr) {
        win->window_pos_cb(win, x, y);
    }

    win->x = x;
    win->y = y;
}

void arqanore::Window::window_close_callback(GLFWwindow *handle) {
    auto win = (Window *) glfwGetWindowUserPointer(handle);

    if (win->window_close_cb != nullptr) {
        win->window_close_cb(win);
        win->window_close_cb = nullptr;
    }
}

void arqanore::Window::key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods) {
    if (key == -1) {
        return;
    }

    Keyboard::scancode = scancode;

    if (action == GLFW_PRESS) {
        Keyboard::states[key] = 1;
    }
    if (action == GLFW_REPEAT) {
        Keyboard::states[key] = 3;
    }
    if (action == GLFW_RELEASE && Keyboard::states[key] > 0) {
        Keyboard::states[key] = 4;
    }
}

void arqanore::Window::mouse_button_callback(GLFWwindow *handle, int button, int action, int mods) {
    if (button == -1) {
        return;
    }

    if (action == 1) {
        Mouse::states[button] = 1;
    }

    if (action == 0 && Mouse::states[button] == 2) {
        Mouse::states[button] = 3;
    }
}

void arqanore::Window::cursor_position_callback(GLFWwindow *handle, double xpos, double ypos) {
    // This is a fix to prevent the move_x and move_y values to go out of control
    if (Mouse::prev_x == 0 && Mouse::prev_y == 0) {
        Mouse::prev_x = (float)xpos;
        Mouse::prev_y = (float)ypos;
    }

    Mouse::prev_x = Mouse::x;
    Mouse::prev_y = Mouse::y;
    Mouse::x = (float)xpos;
    Mouse::y = (float)ypos;
    Mouse::move_x = Mouse::prev_x - Mouse::x;
    Mouse::move_y = Mouse::prev_y - Mouse::y;
}

void arqanore::Window::character_callback(GLFWwindow *handle, unsigned int codepoint) {
    auto win = (Window *) glfwGetWindowUserPointer(handle);

    if (win->window_char_cb != nullptr) {
        win->window_char_cb(win, codepoint);
    }
}

void arqanore::Window::scroll_callback(GLFWwindow *handle, double xoffset, double yoffset) {
    Mouse::scroll_x = (int) xoffset;
    Mouse::scroll_y = (int) yoffset;
}

int arqanore::Window::get_width() {
    return this->width;
}

int arqanore::Window::get_height() {
    return this->height;
}

int arqanore::Window::get_x() {
    return this->x;
}

int arqanore::Window::get_y() {
    return this->y;
}

bool arqanore::Window::get_vsync() {
    return this->vsync;
}

std::string arqanore::Window::get_title() {
    return this->title;
}

arqanore::Color arqanore::Window::get_clear_color() {
    return this->clear_color;
}

std::string arqanore::Window::get_version() {
    auto value = glGetString(GL_VERSION);
    auto result = std::string((const char *) value);

    return result;
}

double arqanore::Window::get_fps() {
    return fps;
}

void arqanore::Window::set_x(int value) {
    this->x = value;
    glfwSetWindowPos(handle, this->x, this->y);
}

void arqanore::Window::set_y(int value) {
    this->y = value;
    glfwSetWindowPos(handle, this->x, this->y);
}

void arqanore::Window::set_width(int value) {
    this->width = value;
    glfwSetWindowSize(handle, this->width, this->height);
}

void arqanore::Window::set_height(int value) {
    this->height = value;
    glfwSetWindowSize(handle, this->width, this->height);
}

void arqanore::Window::set_vsync(bool value) {
    this->vsync = value;

    if (vsync) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}

void arqanore::Window::set_clear_color(arqanore::Color value) {
    this->clear_color = value;
}

void arqanore::Window::set_title(std::string value) {
    this->title = value;
    glfwSetWindowTitle(handle, value.c_str());
}

arqanore::Window::Window() {
    this->width = 1440;
    this->height = 786;
    this->title = "Game Window";
    this->handle = nullptr;
    this->x = 0;
    this->y = 0;
    this->clear_color = Color(0, 0, 0, 255);
    this->vsync = true;
    this->fps = 0;

    this->window_open_cb = nullptr;
    this->window_tick_cb = nullptr;
    this->window_update_cb = nullptr;
    this->window_render2d_cb = nullptr;
    this->window_render3d_cb = nullptr;
    this->window_close_cb = nullptr;
    this->window_resize_cb = nullptr;
    this->window_pos_cb = nullptr;
    this->window_char_cb = nullptr;
    this->window_opengl_cb = nullptr;
}

arqanore::Window::Window(int width, int height, std::string title) : Window() {
    this->width = width;
    this->height = height;
    this->title = title;
}

void arqanore::Window::open(bool fullscreen, bool resizable) {
    init(fullscreen, resizable);
    loop();
}

void arqanore::Window::init(bool fullscreen, bool resizable) {
    setlocale(LC_ALL, "en_US.utf8");

    if (!glfwInit()) {
        throw ArqanoreException("Failed to initialize GLFW");
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    if (fullscreen) {
        handle = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    } else {
        handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    if (handle == nullptr) {
        throw ArqanoreException("Failed to create window");
    }

    glfwMakeContextCurrent(handle);

    if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress)) {
        throw ArqanoreException("Failed to initialize GLAD");
    }

    glfwSwapInterval(1);
    glfwSetWindowUserPointer(handle, this);
    glfwSetWindowCloseCallback(handle, window_close_callback);
    glfwSetWindowSizeCallback(handle, window_resize_callback);
    glfwSetWindowPosCallback(handle, window_pos_callback);
    glfwSetKeyCallback(handle, key_callback);
    glfwSetMouseButtonCallback(handle, mouse_button_callback);
    glfwSetCursorPosCallback(handle, cursor_position_callback);
    glfwSetCharCallback(handle, character_callback);
    glfwSetScrollCallback(handle, scroll_callback);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(this->opengl_debug_callback, this);

    Physics::init();
}

void arqanore::Window::loop() {
    float time_step = 1.f / 60.f;
    double previous_time = glfwGetTime();
    double accum = 0.0;
    double fps_count = 0;
    double fps_time = 0;

    Audio::init();
    Shaders::init();
    Renderer::reset();
    Scene::reset();

    if (window_open_cb != nullptr) {
        window_open_cb(this);
    }

    while (!glfwWindowShouldClose(handle)) {
        double current_time = glfwGetTime();
        double delta_time = current_time - previous_time;
        previous_time = current_time;

        // Calculate fps
        fps_count++;

        if (current_time - fps_time >= 1.0) {
            this->fps = fps_count;

            fps_count = 0;
            fps_time = current_time;
        }

        // Fix delta time to prevent lock
        if (delta_time > 0.25) {
            delta_time = 0.25;
        }

        // Fixed time step loop
        accum += delta_time;

        while (accum >= time_step) {
            if (window_tick_cb != nullptr) {
                window_tick_cb(this, time_step);
            }

            Physics::update(time_step);
            accum -= time_step;
        }

        if (window_update_cb != nullptr) {
            window_update_cb(this, accum / time_step);
        }

        Keyboard::update();
        Mouse::update();

        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, width, height);
        glClearColor(this->clear_color.r / 255.0, this->clear_color.g / 255.0, this->clear_color.b / 255.0, this->clear_color.a / 255.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (window_render3d_cb != nullptr) {
            window_render3d_cb(this);
        }

        if (window_render2d_cb != nullptr) {
            glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);

            window_render2d_cb(this);
        }

        Renderer::reset();

        glfwSwapBuffers(handle);
        glfwPollEvents();
    }

    if (window_close_cb != nullptr) {
        window_close_cb(this);
    }

    Audio::stop();
    Audio::destroy();

    glfwTerminate();
}

void arqanore::Window::close() {
    glfwSetWindowShouldClose(handle, 1);
}

void arqanore::Window::on_open(void (*cb)(Window *)) {
    window_open_cb = cb;
}

void arqanore::Window::on_tick(void (*cb)(Window *, double)) {
    window_tick_cb = cb;
}

void arqanore::Window::on_update(void (*cb)(Window *, double)) {
    window_update_cb = cb;
}

void arqanore::Window::on_render2d(void (*cb)(Window *)) {
    window_render2d_cb = cb;
}

void arqanore::Window::on_render3d(void (*cb)(Window *)) {
    window_render3d_cb = cb;
}

void arqanore::Window::on_close(void (*cb)(Window *)) {
    window_close_cb = cb;
}

void arqanore::Window::on_resize(void (*cb)(Window *, int, int)) {
    window_resize_cb = cb;
}

void arqanore::Window::on_position(void (*cb)(Window *, int, int)) {
    window_pos_cb = cb;
}

void arqanore::Window::on_char(void (*cb)(Window *, unsigned int)) {
    window_char_cb = cb;
}

void arqanore::Window::on_opengl(void (*cb)(Window *, std::string, std::string, std::string)) {
    window_opengl_cb = cb;
}