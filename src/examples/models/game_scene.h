#pragma once

#include "floor.h"
#include "tit.h"

class GameScene {
private:
    static std::vector<Floor> floors;
    static std::vector<Tit> tits;
    static arqanore::Vector3 camera_pos;
    static arqanore::Vector3 camera_pos_prev;
    static arqanore::Vector3 camera_pos_next;
    static arqanore::Vector3 camera_rot;

    static void update_objects(double at);

    static void update_camera(double ts);

    static int count_tits();

public:
    static void init();

    static void tick(arqanore::Window *window, double dt);

    static void update(arqanore::Window *window, double at);

    static void render2D(arqanore::Window *window);

    static void render3D(arqanore::Window *window);
};