#include "trainingmenu.hpp"
#include <algorithm>
#include <raylib.h>

TrainingState TrainingMenu::handleTrainingSubMode() {
    switch (macroSelection) {
        // GENERAL -------------------------------------------
        case TrainingMenuMacroSelection::GENERAL:
            //events
           	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
           	    choiceOnGeneral--;
                sys->soundManager->playCurrent();

                game_manager->cameras[1].target.y =
                    (float)choiceOnGeneral*(scrollableHeight/(float)SettingModSelection::EXIT);
           	}

           	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
           	    choiceOnGeneral++;
                sys->soundManager->playCurrent();

                game_manager->cameras[1].target.y =
                    (float)choiceOnGeneral*(scrollableHeight/(float)SettingModSelection::EXIT);
           	}

           	if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {// right
                switch (choiceOnGeneral) {
                    case SettingModSelection::INDEX:
                        macroSelection++;
                        game_manager->cameras[1].target.y = 0.0f;
                        break;
                    case SettingModSelection::MASTERVOLUME:
                        sys->soundManager->incrementGlobalVolume();
                        break;
                    case SettingModSelection::MUSICVOLUME:
                        sys->soundManager->incrementMusicVolume();
                        break;
                    case SettingModSelection::EFFECTSVOLUME:
                        sys->soundManager->incrementSfxVolume();
                        break;
                    case SettingModSelection::DISPLAYMODE:
                        switch (sys->getDisplayMode()) {
                            case DisplayMode::BORDERLESS_WINDOW:
                                sys->resetWindow();
                                break;
                            case DisplayMode::RESIZABLE_WINDOW:
                                sys->setFullScreen();
                                break;
                            case DisplayMode::FULLSCREEN:
                                sys->setBorderlessWindow();
                                break;
                        }
                        break;
                    case SettingModSelection::RESOLUTION:
                        if(sys->getDisplayMode() == DisplayMode::RESIZABLE_WINDOW) {
                            const auto [screenW, screenH] = sys->getScreenSizeWH();
                            sys->resizeWindowByWidth(screenW+64);
                        }
                        break;
                    case SettingModSelection::FPS:
                        sys->incrementFPS();
                        break;
                    case SettingModSelection::VSYNC:
                        sys->toggleVsync();
                        break;
                    default:
                        break;
                }
           	}

           	if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {// left
                switch (choiceOnGeneral) {
                    case SettingModSelection::INDEX:
                        macroSelection--;
                        game_manager->cameras[1].target.y = 0.0f;
                        break;
                    case SettingModSelection::MASTERVOLUME:
                        sys->soundManager->decrementGlobalVolume();
                        break;
                    case SettingModSelection::MUSICVOLUME:
                        sys->soundManager->decrementMusicVolume();
                        break;
                    case SettingModSelection::EFFECTSVOLUME:
                        sys->soundManager->decrementSfxVolume();
                        break;
                    case SettingModSelection::DISPLAYMODE:
                        switch (sys->getDisplayMode()) {
                            case DisplayMode::BORDERLESS_WINDOW:
                                sys->setFullScreen();
                                break;
                            case DisplayMode::FULLSCREEN:
                                sys->resetWindow();
                                break;
                            case DisplayMode::RESIZABLE_WINDOW:
                                sys->setBorderlessWindow();
                                break;
                        }
                        break;
                    case SettingModSelection::RESOLUTION:
                        if(sys->getDisplayMode() == DisplayMode::RESIZABLE_WINDOW) {
                            const auto [screenW, screenH] = sys->getScreenSizeWH();
                            sys->resizeWindowByWidth(screenW-64);
                        }
                        break;
                    case SettingModSelection::FPS:
                        sys->decrementFPS();
                        break;
                    case SettingModSelection::VSYNC:
                        sys->toggleVsync();
                        break;
                    default:
                        break;
                }
           	}

           	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {
                switch (choiceOnGeneral) {
                    case SettingModSelection::RESETAUDIO:
                        sys->soundManager->resetVolume();
                        break;
                    case SettingModSelection::RESETVIDEO:
                        sys->resetVideo();
                        break;
                    case SettingModSelection::RESUME:
                        return TrainingState::IN_GAME;
                    case SettingModSelection::EXIT:
                        return TrainingState::GOTO_LOBBY;
                    default:
                        break;
                }
           	}
            break;

        // PLAYER -------------------------------------------
        case TrainingMenuMacroSelection::PLAYER:
            // events
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {// up
           	    choiceOnPlayer--;
                sys->soundManager->playCurrent();

                game_manager->cameras[1].target.y =
                    (float)choiceOnPlayer*(scrollableHeight/(float)PlayerModSelection::EXIT);
           	}

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {// down
           	    choiceOnPlayer++;
                sys->soundManager->playCurrent();

                game_manager->cameras[1].target.y =
                    (float)choiceOnPlayer*(scrollableHeight/(float)PlayerModSelection::EXIT);
           	}

            if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {// right
                switch (choiceOnPlayer) {
                    case PlayerModSelection::INDEX:
                        macroSelection++;
                        game_manager->cameras[1].target.y = 0.0f;
                        break;
                    case PlayerModSelection::SKIN:
                        currPlayerSkinIndex++;
                        if(currPlayerSkinIndex >= playerSkinsInfo.size())
                            currPlayerSkinIndex = 0;
                        break;
                    case PlayerModSelection::HP:
                        game_manager->players[0].setHealth(
                            game_manager->players[0].getHealth()+((Player::getMaxHealth()-Player::getMinHealth())/30)
                        );
                        break;
                    case PlayerModSelection::MOVEMENT_SPEED:
                        game_manager->players[0].setMoveVel(
                            game_manager->players[0].getMoveVel()+((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::ATTACK_SPEED:
                        game_manager->players[0].setAttackVel(
                            game_manager->players[0].getAttackVel()+((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::ATTACK_COOLDOWN:
                        game_manager->players[0].setAttackCooldown(
                            game_manager->players[0].getAttackCooldown()+0.2f
                        );
                        break;
                    case PlayerModSelection::KUNAI_SPEED:
                        game_manager->players[0].setKunaiVel(
                            game_manager->players[0].getKunaiVel()+((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::DIMENSION:
                        game_manager->players[0].setPlayerDimensionMul(
                            game_manager->players[0].getPlayerDimensionMul()+((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::KUNAI_DIMENSION:
                        game_manager->players[0].setKunaiDimensionMul(
                            game_manager->players[0].getKunaiDimensionMul()+((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::KUNAI_DAMAGE:
                        game_manager->players[0].setKunaiDamageMul(
                            game_manager->players[0].getKunaiDamageMul()+((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::ULT:
                        break;
                    default:
                        break;
                }
            }

            if  (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {// left
                switch (choiceOnPlayer) {
                    case PlayerModSelection::INDEX:
                        macroSelection--;
                        game_manager->cameras[1].target.y = 0.0f;
                        break;
                    case PlayerModSelection::SKIN:
                        if(currPlayerSkinIndex <= 0) currPlayerSkinIndex = playerSkinsInfo.size()-1;
                        else currPlayerSkinIndex--;

                        break;
                    case PlayerModSelection::HP:
                        game_manager->players[0].setHealth(
                            game_manager->players[0].getHealth()-((Player::getMaxHealth()-Player::getMinHealth())/30)
                        );
                        break;
                    case PlayerModSelection::MOVEMENT_SPEED:
                        game_manager->players[0].setMoveVel(
                            game_manager->players[0].getMoveVel()-((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::ATTACK_SPEED:
                        game_manager->players[0].setAttackVel(
                            game_manager->players[0].getAttackVel()-((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::ATTACK_COOLDOWN:
                        game_manager->players[0].setAttackCooldown(
                            game_manager->players[0].getAttackCooldown()-0.2f
                        );
                        break;
                    case PlayerModSelection::KUNAI_SPEED:
                        game_manager->players[0].setKunaiVel(
                            game_manager->players[0].getKunaiVel()-((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::DIMENSION:
                        game_manager->players[0].setPlayerDimensionMul(
                            game_manager->players[0].getPlayerDimensionMul()-((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::KUNAI_DIMENSION:
                        game_manager->players[0].setKunaiDimensionMul(
                            game_manager->players[0].getKunaiDimensionMul()-((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::KUNAI_DAMAGE:
                        game_manager->players[0].setKunaiDamageMul(
                            game_manager->players[0].getKunaiDamageMul()-((Player::getMaxMul()-Player::getMinMul())/30)
                        );
                        break;
                    case PlayerModSelection::ULT:
                        break;
                    default:
                        break;
                }
            }

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {
                switch (choiceOnPlayer) {
                    case PlayerModSelection::RESET_PLAYER:
                        game_manager->players[0].resetModifiers();
                        break;
                    case PlayerModSelection::RESUME:
                        return TrainingState::IN_GAME;
                        break;
                    case PlayerModSelection::EXIT:
                        return TrainingState::GOTO_LOBBY;
                        break;
                    default:
                        break;
                }
            }
            break;

        // ENEMY -------------------------------------------
        case TrainingMenuMacroSelection::ENEMY:
            // events
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {// up
           	    choiceOnEnemy--;
                sys->soundManager->playCurrent();

                game_manager->cameras[1].target.y =
                    (float)choiceOnEnemy*(scrollableHeight/(float)EnemyModSelection::EXIT);
           	}

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {// down
           	    choiceOnEnemy++;
                sys->soundManager->playCurrent();

                game_manager->cameras[1].target.y =
                    (float)choiceOnEnemy*(scrollableHeight/(float)EnemyModSelection::EXIT);
           	}

            if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {// right
                switch (choiceOnEnemy) {
                    case EnemyModSelection::INDEX:
                        macroSelection++;
                        game_manager->cameras[1].target.y = 0.0f;
                        break;
                    case EnemyModSelection::TYPE:
                        break;
                    case EnemyModSelection::GENERATION_CRITERIA:
                        break;
                    case EnemyModSelection::HP:
                        break;
                    case EnemyModSelection::STRENGHT:
                        break;
                    case EnemyModSelection::MOVEMENT_SPEED:
                        break;
                    case EnemyModSelection::ATTACK_SPEED:
                        break;
                    case EnemyModSelection::DIMENSION:
                        break;
                    case EnemyModSelection::BEHAVIOUR:
                        break;
                    default:
                        break;
                }
            }

            if  (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {// left
                switch (choiceOnEnemy) {
                    case EnemyModSelection::INDEX:
                        macroSelection--;
                        game_manager->cameras[1].target.y = 0.0f;
                        break;
                    case EnemyModSelection::TYPE:
                        break;
                    case EnemyModSelection::GENERATION_CRITERIA:
                        break;
                    case EnemyModSelection::HP:
                        break;
                    case EnemyModSelection::STRENGHT:
                        break;
                    case EnemyModSelection::MOVEMENT_SPEED:
                        break;
                    case EnemyModSelection::ATTACK_SPEED:
                        break;
                    case EnemyModSelection::DIMENSION:
                        break;
                    case EnemyModSelection::BEHAVIOUR:
                        break;
                    default:
                        break;
                }
            }

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {
                switch (choiceOnEnemy) {
                    case EnemyModSelection::RESUME:
                        return TrainingState::IN_GAME;
                        break;
                    case EnemyModSelection::EXIT:
                        return TrainingState::GOTO_LOBBY;
                        break;
                    default:
                        break;
                }
            }
            break;
    }

    if(IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_X)) {
        return TrainingState::IN_GAME;
    }

    return TrainingState::CONTINUE;
}
