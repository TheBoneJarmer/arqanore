#include <stdexcept>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "arqanore/font.h"
#include "arqanore/shaders.h"
#include "glad/gl.h"
#include "arqanore/exceptions.h"

void arqanore::Font::generate_glyphs(std::string &path) {
    FT_Library ft_lib;
    FT_Face ft_face;

    if (FT_Init_FreeType(&ft_lib)) {
        throw ArqanoreException("Could not init FreeType library");
    }

    if (FT_New_Face(ft_lib, path.c_str(), 0, &ft_face)) {
        throw ArqanoreException("Failed to load font. Make sure the file exists and is a valid TrueType font.");
    }

    FT_Set_Pixel_Sizes(ft_face, this->pixel_width, this->pixel_height);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(ft_face, c, FT_LOAD_RENDER)) {
            std::cerr << "Failed to parse glyph " << c << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, ft_face->glyph->bitmap.buffer);

        Glyph glyph = {
                texture,
                ft_face->glyph->bitmap.width,
                ft_face->glyph->bitmap.rows,
                ft_face->glyph->bitmap_left,
                ft_face->glyph->bitmap_top,
                ft_face->glyph->advance.x
        };

        glyphs[c] = glyph;
    }

    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_lib);
}

void arqanore::Font::generate_buffers() {
    int vertices_count = 128 * 12;
    int i = 0;
    float vertices[vertices_count];
    float texcoords[vertices_count];

    for (const auto &glyph: glyphs) {
        texcoords[i + 0] = 0;
        texcoords[i + 1] = 0;
        texcoords[i + 2] = 1;
        texcoords[i + 3] = 0;
        texcoords[i + 4] = 0;
        texcoords[i + 5] = 1;
        texcoords[i + 6] = 1;
        texcoords[i + 7] = 0;
        texcoords[i + 8] = 0;
        texcoords[i + 9] = 1;
        texcoords[i + 10] = 1;
        texcoords[i + 11] = 1;

        vertices[i + 0] = 0;
        vertices[i + 1] = 0;
        vertices[i + 2] = glyph.width;
        vertices[i + 3] = 0;
        vertices[i + 4] = 0;
        vertices[i + 5] = glyph.height;
        vertices[i + 6] = glyph.width;
        vertices[i + 7] = 0;
        vertices[i + 8] = 0;
        vertices[i + 9] = glyph.height;
        vertices[i + 10] = glyph.width;
        vertices[i + 11] = glyph.height;

        i += 12;
    }

    int position_attrib = glGetAttribLocation(Shaders::font.id, "a_position");
    int texcoord_attrib = glGetAttribLocation(Shaders::font.id, "a_texcoord");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(position_attrib);

    glGenBuffers(1, &vbo_texcoords);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), texcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(texcoord_attrib);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

arqanore::Font::Font() {

}

arqanore::Font::Font(std::string path, unsigned int width, unsigned int height) {
    this->pixel_width = width;
    this->pixel_height = height;

    generate_glyphs(path);
    generate_buffers();
}

float arqanore::Font::measure(std::string text) {
    float result = 0;

    for (char &c: text) {
        Glyph *glyph = &glyphs[c];
        result += glyph->advance >> 6;
    }

    return result;
}
