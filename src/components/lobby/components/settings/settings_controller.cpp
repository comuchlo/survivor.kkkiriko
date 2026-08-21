#include "settings.hpp"

LobbyState Settings::handleLobbySubMode() {
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
                    case DisplayMode::RESIZABLE_WINDOW:
                        sys->setFullScreen();
                        break;
                    case DisplayMode::FULLSCREEN:
                        sys->setBorderlessWindow();
                        break;
                }
                break;
            case SettingSelection::RESOLUTION:
                if(sys->getDisplayMode() == DisplayMode::RESIZABLE_WINDOW) {
                    const auto [screenW, screenH] = sys->getScreenSizeWH();
                    sys->resizeWindowByWidth(screenW+64);
                }
                break;
            case SettingSelection::FPS:
                sys->incrementFPS();
                break;
            case SettingSelection::VSYNC:
                sys->toggleVsync();
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
                    sys->resizeWindowByWidth(screenW-64);
                }
                break;
            case SettingSelection::FPS:
                sys->decrementFPS();
                break;
            case SettingSelection::VSYNC:
                sys->toggleVsync();
                break;
            default:
                break;
        }
	}

	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {
        switch (choice) {
            case SettingSelection::RESETAUDIO:
                sys->soundManager->resetVolume();
                break;
            case SettingSelection::RESETVIDEO:
                sys->resetVideo();
                break;
            case SettingSelection::EXIT:
                return LobbyState::MENU; // temp
            default:
                break;
        }
	}

	if(IsKeyPressed(KEY_X)){
	    return LobbyState::MENU;
	}

	return LobbyState::CONTINUE_SELF;
}
