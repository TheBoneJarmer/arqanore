#pragma once

#include <iostream>
#include "arqanore/model.h"
#include "arqanore/exceptions.h"
#include "arqanore/window.h"
#include "arqanore/font.h"

class GameAssets {
public:
    static arqanore::Model* model_tit;

    static arqanore::Model* model_floor;

    static arqanore::Font* font;

    static void load(arqanore::Window* window);

    static void dispose();
};