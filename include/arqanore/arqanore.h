#pragma once

namespace arqanore {
    class Arqanore {
    public:
        static std::string get_opengl_version();
        
        static std::string get_version();
        
        static unsigned int get_version_major();
        
        static unsigned int get_version_minor();
        
        static unsigned int get_version_patch();
    };
}
