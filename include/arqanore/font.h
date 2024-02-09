#pragma once

#include <cstdlib>
#include "shader.h"
#include "window.h"

namespace arqanore {
    struct Glyph {
        unsigned int id;
        unsigned int width;
        unsigned int height;
        int left;
        int top;
        long advance;
    };

    class Font {
        friend class Renderer;

    private:
        Glyph glyphs[128];
        unsigned int vbo_vertices;
        unsigned int vbo_texcoords;
        unsigned int vao;
        unsigned int pixel_width;
        unsigned int pixel_height;

        void generate_glyphs(std::string &path);

        void generate_buffers();

    public:
        Font();

        Font(std::string path, unsigned int width, unsigned int height);

        float measure(std::string text);
    };
}
