#include "trainingmenu.hpp"

TrainingMenu::TrainingMenu() {
    game_manager = GameManager::getInstance();
    game_manager->resetCamera1();
    drawer = DrawManager::getInstance();
    drawer->switchRender(); // preserve last frame draws as background
}
