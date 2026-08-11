#include "settings.hpp"

ControllerExitCode Settings::handleModality() {
    //events
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
	    choice--;
        sys->soundManager->playCurrent();
	}

	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
	    choice++;
        sys->soundManager->playCurrent();
	}

	if  (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {//right
        switch (choice) {
            case SettingSelection::MASTERVOLUME:
                sys->soundManager->incrementGlobalVolume();
                break;
            case SettingSelection::MUSICVOLUME:
                sys->soundManager->incrementMusicVolume();
                break;
            case SettingSelection::EFFECTSVOLUME:
                sys->soundManager->incrementSfxVolume();
                break;
            case SettingSelection::DISPLAYMODE:
                switch (sys->getDisplayMode()) {
                    case DisplayMode::BORDERLESS_WINDOW:
                        sys->resetWindow();
                        break;
                    case DisplayMode::FULLSCREEN:
                        sys->setBorderlessWindow();
                        break;
                    case DisplayMode::RESIZABLE_WINDOW:
                        sys->setFullScreen();
                        break;
                }
                break;
            case SettingSelection::RESOLUTION:
                if(sys->getDisplayMode() == DisplayMode::RESIZABLE_WINDOW) {
                    const auto [screenW, screenH] = sys->getScreenSizeWH();
                    sys->resizeWindowByWidth(screenW+10);
                }
                break;
            default:
                break;
        }
	}

	if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {//left
        switch (choice) {
            case SettingSelection::MASTERVOLUME:
                sys->soundManager->decrementGlobalVolume();
                break;
            case SettingSelection::MUSICVOLUME:
                sys->soundManager->decrementMusicVolume();
                break;
            case SettingSelection::EFFECTSVOLUME:
                sys->soundManager->decrementSfxVolume();
                break;
            case SettingSelection::DISPLAYMODE:
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
            case SettingSelection::RESOLUTION:
                if(sys->getDisplayMode() == DisplayMode::RESIZABLE_WINDOW) {
                    const auto [screenW, screenH] = sys->getScreenSizeWH();
                    sys->resizeWindowByWidth(screenW-10);
                }
                break;
            default:
                break;
        }
	}

	if (IsKeyPressed(KEY_ENTER)) {
        switch (choice) {
            case SettingSelection::RESETAUDIO:
                sys->soundManager->resetVolume();
                break;
            case SettingSelection::RESETVIDEO:
                sys->resetWindow();
                break;
            case SettingSelection::EXIT:
                return ControllerExitCode::GOTO_LOBBY; // temp
            default:
                break;
        }
	}

	return ControllerExitCode::CONTINUE;
}
