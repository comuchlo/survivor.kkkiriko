#include "trainingmenu.hpp"
#include <cstring>
#include <stdexcept>

TrainingMenuMacroSelection& operator++(TrainingMenuMacroSelection& val) {
    if (val == TrainingMenuMacroSelection::ENEMY){
        val = TrainingMenuMacroSelection::GENERAL;
    }else{
        val = static_cast<TrainingMenuMacroSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

TrainingMenuMacroSelection operator++(TrainingMenuMacroSelection& val, int) {
  TrainingMenuMacroSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

TrainingMenuMacroSelection& operator--(TrainingMenuMacroSelection& val) {
    if (val == TrainingMenuMacroSelection::GENERAL){
        val = TrainingMenuMacroSelection::ENEMY;
    }else{
        val = static_cast<TrainingMenuMacroSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

TrainingMenuMacroSelection operator--(TrainingMenuMacroSelection& val, int) {
  TrainingMenuMacroSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

SettingModSelection& operator++(SettingModSelection& val) {
    if (val == SettingModSelection::EXIT){
        val = SettingModSelection::INDEX;
    }else{
        val = static_cast<SettingModSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

SettingModSelection operator++(SettingModSelection& val, int) {
  SettingModSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

SettingModSelection& operator--(SettingModSelection& val) {
    if (val == SettingModSelection::INDEX){
        val = SettingModSelection::EXIT;
    }else{
        val = static_cast<SettingModSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

SettingModSelection operator--(SettingModSelection& val, int) {
  SettingModSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

PlayerModSelection& operator++(PlayerModSelection& val){
    if (val == PlayerModSelection::EXIT){
        val = PlayerModSelection::INDEX;
    }else{
        val = static_cast<PlayerModSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

PlayerModSelection operator++(PlayerModSelection& val, int)
{
  PlayerModSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

PlayerModSelection& operator--(PlayerModSelection& val){
    if (val == PlayerModSelection::INDEX){
        val = PlayerModSelection::EXIT;
    }else{
        val = static_cast<PlayerModSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

PlayerModSelection operator--(PlayerModSelection& val, int)
{
  PlayerModSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

EnemyModSelection& operator++(EnemyModSelection& val){
    if (val == EnemyModSelection::EXIT){
        val = EnemyModSelection::INDEX;
    }else{
        val = static_cast<EnemyModSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

EnemyModSelection operator++(EnemyModSelection& val, int)
{
  EnemyModSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

EnemyModSelection& operator--(EnemyModSelection& val){
    if (val == EnemyModSelection::INDEX){
        val = EnemyModSelection::EXIT;
    }else{
        val = static_cast<EnemyModSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

EnemyModSelection operator--(EnemyModSelection& val, int)
{
  EnemyModSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}


TrainingMenu::TrainingMenu(Player* playerParams) {
    game_manager = GameManager::getInstance();
    drawer = DrawManager::getInstance();

    game_manager->resetCamera(1);

    // choice
    macroSelection = TrainingMenuMacroSelection::GENERAL;
    choiceOnGeneral = SettingModSelection::INDEX;
    choiceOnPlayer = PlayerModSelection::INDEX;
    choiceOnEnemy = EnemyModSelection::INDEX;

    // player params
    this->playerParams = playerParams;

    // player skin infos
    playerSkinsInfo = drawer->getPlayerSkinsInfo();
    std::string currPlayerSkinName = game_manager->players[0].getSkinName();

    for(oldPlayerSkinIndex = 0; oldPlayerSkinIndex < playerSkinsInfo.size(); oldPlayerSkinIndex++) {
        if(currPlayerSkinName.compare(playerSkinsInfo[oldPlayerSkinIndex].name) == 0) {
            break;
        }
    }

    if(oldPlayerSkinIndex == playerSkinsInfo.size()) {
        throw std::out_of_range("Error trying to acess playerSkinsInfo out of bound");
    }

    currPlayerSkinName = oldPlayerSkinIndex;

    drawer->switchRender(); // preserve last frame draws as background
}

TrainingMenu::~TrainingMenu() {
    //before resuming:

    // load player skin if changed
    if(oldPlayerSkinIndex != currPlayerSkinIndex) {
        std::string newSkinName = playerSkinsInfo[currPlayerSkinIndex].name;
        drawer->unloadPlayerSkins();
        game_manager->players[0].setSkin(drawer->loadPlayerSkin(newSkinName));

    }
}
