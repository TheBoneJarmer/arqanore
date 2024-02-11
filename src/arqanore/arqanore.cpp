#include <string>
#include <vector>
#include "glad/gl.h"
#include "arqanore/arqanore.h"
#include "arqanore/utils.h"

std::string arqanore::Arqanore::get_opengl_version() {
    const unsigned char* value = glGetString(GL_VERSION);
    std::string result = std::string((const char *) value);

    return result;
}

std::string arqanore::Arqanore::get_version() {
    return std::string(VERSION);
}

unsigned int arqanore::Arqanore::get_version_major() {
    std::vector<std::string> values = string_split(VERSION, '.');
    unsigned int value = std::stoi(values[0]);
    
    return value;
}

unsigned int arqanore::Arqanore::get_version_minor() {
    std::vector<std::string> values = string_split(VERSION, '.');
    unsigned int value = std::stoi(values[1]);
    
    return value;
}

unsigned int arqanore::Arqanore::get_version_patch() {
    std::vector<std::string> values = string_split(VERSION, '.');
    unsigned int value = std::stoi(values[2]);
    
    return value;
}
