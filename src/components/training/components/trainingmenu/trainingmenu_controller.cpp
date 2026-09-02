#include "trainingmenu.hpp"
#include <raylib.h>

TrainingState TrainingMenu::handleTrainingSubMode() {
    switch (macroSelection) {
        // GENERAL -------------------------------------------
        case TrainingMenuMacroSelection::GENERAL:
            //events
           	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
           	    choiceOnGeneral--;
                sys->soundManager->playCurrent();
           	}

           	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
           	    choiceOnGeneral++;
                sys->soundManager->playCurrent();
           	}

           	if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {//right
                switch (choiceOnGeneral) {
                    case SettingModSelection::INDEX:
                        macroSelection++;
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

           	if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {//left
                switch (choiceOnGeneral) {
                    case SettingModSelection::INDEX:
                        macroSelection--;
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

           	if(IsKeyPressed(KEY_X)){
           	    return TrainingState::IN_GAME;
           	}
            break;

        // PLAYER -------------------------------------------
        case TrainingMenuMacroSelection::PLAYER:
            // events
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
           	    choiceOnPlayer--;
                sys->soundManager->playCurrent();
           	}

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
           	    choiceOnPlayer++;
                sys->soundManager->playCurrent();
           	}

            if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {//right
                switch (choiceOnPlayer) {
                    case PlayerModSelection::INDEX:
                        macroSelection++;
                        break;
                    case PlayerModSelection::SKIN:
                        break;
                    case PlayerModSelection::HP:
                        break;
                    case PlayerModSelection::STRENGHT:
                        break;
                    case PlayerModSelection::MOVEMENT_SPEED:
                        break;
                    case PlayerModSelection::ATTACK_SPEED:
                        break;
                    case PlayerModSelection::DIMENSION:
                        break;
                    case PlayerModSelection::ULT:
                        break;
                    default:
                        break;
                }
            }

            if  (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {//right
                switch (choiceOnPlayer) {
                    case PlayerModSelection::INDEX:
                        macroSelection--;
                        break;
                    case PlayerModSelection::SKIN:
                        break;
                    case PlayerModSelection::HP:
                        break;
                    case PlayerModSelection::STRENGHT:
                        break;
                    case PlayerModSelection::MOVEMENT_SPEED:
                        break;
                    case PlayerModSelection::ATTACK_SPEED:
                        break;
                    case PlayerModSelection::DIMENSION:
                        break;
                    case PlayerModSelection::ULT:
                        break;
                    default:
                        break;
                }
            }

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {
                switch (choiceOnPlayer) {
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

            if(IsKeyPressed(KEY_X)){
           	    return TrainingState::IN_GAME;
           	}

            break;

        // ENEMY -------------------------------------------
        case TrainingMenuMacroSelection::ENEMY:
            // events
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
           	    choiceOnEnemy--;
                sys->soundManager->playCurrent();
           	}

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
           	    choiceOnEnemy++;
                sys->soundManager->playCurrent();
           	}

            if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {//right
                switch (choiceOnEnemy) {
                    case EnemyModSelection::INDEX:
                        macroSelection++;
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

            if  (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {//right
                switch (choiceOnEnemy) {
                    case EnemyModSelection::INDEX:
                        macroSelection--;
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

            if(IsKeyPressed(KEY_X)){
           	    return TrainingState::IN_GAME;
           	}

            break;
    }

    return TrainingState::CONTINUE;
}
