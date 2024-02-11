#include <string>
#include "glad/gl.h"
#include "arqanore/arqanore.h"

std::string arqanore::Arqanore::get_opengl_version() {
    const unsigned char* value = glGetString(GL_VERSION);
    std::string result = std::string((const char *) value);

    return result;
}

std::string arqanore::Arqanore::get_version() {
    return std::string(VERSION);
}
