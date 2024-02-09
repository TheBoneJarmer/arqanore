#include "game_assets.h"
#include "arqanore/shaders.h"
#include "arqanore/shadersources.h"

arqanore::Model *GameAssets::model_floor;
arqanore::Model *GameAssets::model_tit;
arqanore::Font *GameAssets::font;

void GameAssets::load(arqanore::Window *window) {
    try {
        model_tit = new arqanore::Model("assets/models/tit.arqm");
        model_floor = new arqanore::Model("assets/models/floor.arqm");

        // I can't get Blender to export flat surfaces so I introduced this little cheat to fix it
        // The models are not that big anyway so we are good
        //model_tit->calculate_normals(false);
        model_floor->calculate_normals(false);

        font = new arqanore::Font("assets/fonts/arial.ttf", 20, 20);
    } catch (arqanore::ArqanoreException &e) {
        std::cerr << e.what() << std::endl;
        window->close();
    }
}

void GameAssets::dispose() {
    delete model_tit;
    delete model_floor;
    delete font;
}
