#include "game_scene.h"
#include "arqanore/camera.h"
#include "arqanore/scene.h"
#include "arqanore/mouse.h"
#include "arqanore/keyboard.h"
#include "arqanore/mathhelper.h"
#include "arqanore/renderer.h"
#include "game_assets.h"
#include "arqanore/shaders.h"

std::vector<Floor> GameScene::floors;
std::vector<Tit> GameScene::tits;
arqanore::Vector3 GameScene::camera_rot;
arqanore::Vector3 GameScene::camera_pos;
arqanore::Vector3 GameScene::camera_pos_prev;
arqanore::Vector3 GameScene::camera_pos_next;

void GameScene::update_objects(double at) {
    int tit_count = count_tits();

    for (Floor &floor: floors) {
        floor.update(at);
    }

    for (auto &tit: tits) {
        if (tit.is_disposed()) {
            continue;
        }

        tit.update(at);
    }

    if (arqanore::Keyboard::key_pressed(arqanore::Keys::DELETE) || (tit_count == 0 && !tits.empty())) {
        for (Tit &tit: tits) {
            tit.dispose();
        }

        tits.clear();
        std::cout << "Tits cleared" << std::endl;
    }

    if (arqanore::Keyboard::key_down(arqanore::Keys::SPACE)) {
        tits.emplace_back();
    }
}

void GameScene::update_camera(double ts) {
    float speed = 1;

    if (arqanore::Keyboard::key_down(arqanore::Keys::DOWN)) camera_rot.x += 3 * speed;
    if (arqanore::Keyboard::key_down(arqanore::Keys::UP)) camera_rot.x -= 3 * speed;
    if (arqanore::Keyboard::key_down(arqanore::Keys::LEFT)) camera_rot.y -= 3 * speed;
    if (arqanore::Keyboard::key_down(arqanore::Keys::RIGHT)) camera_rot.y += 3 * speed;

    if (arqanore::Keyboard::key_down(arqanore::Keys::Q)) camera_pos_next.y -= speed;
    if (arqanore::Keyboard::key_down(arqanore::Keys::E)) camera_pos_next.y += speed;

    if (arqanore::Keyboard::key_down(arqanore::Keys::W)) {
        camera_pos_next.x -= (float) sin(arqanore::MathHelper::radians(camera_rot.y)) * speed;
        camera_pos_next.z += (float) cos(arqanore::MathHelper::radians(camera_rot.y)) * speed;
    }

    if (arqanore::Keyboard::key_down(arqanore::Keys::S)) {
        camera_pos_next.x += (float) sin(arqanore::MathHelper::radians(camera_rot.y)) * speed;
        camera_pos_next.z -= (float) cos(arqanore::MathHelper::radians(camera_rot.y)) * speed;
    }

    if (arqanore::Keyboard::key_down(arqanore::Keys::A)) {
        camera_pos_next.x -= (float) sin(arqanore::MathHelper::radians(camera_rot.y - 90)) * speed;
        camera_pos_next.z += (float) cos(arqanore::MathHelper::radians(camera_rot.y - 90)) * speed;
    }

    if (arqanore::Keyboard::key_down(arqanore::Keys::D)) {
        camera_pos_next.x -= (float) sin(arqanore::MathHelper::radians(camera_rot.y + 90)) * speed;
        camera_pos_next.z += (float) cos(arqanore::MathHelper::radians(camera_rot.y + 90)) * speed;
    }

    if (arqanore::Keyboard::key_pressed(arqanore::Keys::R)) {
        camera_rot = arqanore::Vector3(35, 0, 0);
        camera_pos = arqanore::Vector3(0, -15, -20);
        camera_pos_next = camera_pos;
        camera_pos_prev = camera_pos_prev;

        std::cout << "Gamescene reset" << std::endl;
    }

    arqanore::Camera &camera = arqanore::Scene::cameras[0];
    camera.position = arqanore::Vector3::lerp(camera_pos_prev, camera_pos_next, ts);
    camera.rotation = arqanore::Quaternion::rotate(arqanore::Quaternion(), camera_rot);

    camera_pos_prev = camera_pos_next;
}

int GameScene::count_tits() {
    int result = 0;

    for (int i = 0; i < tits.size(); i++) {
        Tit &tit = tits[i];

        if (tit.is_disposed()) {
            continue;
        }

        result++;
    }

    return result;
}

void GameScene::init() {
    camera_rot = arqanore::Vector3(35, 0, 0);
    camera_pos = arqanore::Vector3(0, -15, -20);
    camera_pos_next = camera_pos;
    camera_pos_prev = camera_pos;

    for (int x = -10; x < 10; x++) {
        for (int z = -10; z < 10; z++) {
            Floor floor(x * 4.8f, z * 4.8f);
            floors.push_back(floor);
        }
    }

    for (int i=0; i<300; i++) {
        tits.emplace_back();
    }
}

void GameScene::tick(arqanore::Window *window, double dt) {

}

void GameScene::update(arqanore::Window *window, double at) {
    update_objects(at);
    update_camera(at);
}

void GameScene::render2D(arqanore::Window *window) {
    arqanore::Font *font = GameAssets::font;
    arqanore::Renderer::render_text(window, font, "FPS: " + std::to_string(window->get_fps()), arqanore::Vector2(32, 32), arqanore::Color::WHITE);
    arqanore::Renderer::render_text(window, font, "Tits: " + std::to_string(count_tits()), arqanore::Vector2(32, 64), arqanore::Color::WHITE);
}

void GameScene::render3D(arqanore::Window *window) {
    for (Floor &floor: floors) {
        floor.render(window);
    }

    for (Tit &tit: tits) {
        tit.render(window);
    }
}
