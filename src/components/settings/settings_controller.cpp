#include "settings.hpp"


void Settings::handleSettings() {
    //events
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
	    this->choice--;
        this->sys->soundManager->playCurrent();
	}

	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
	    this->choice++;
        this->sys->soundManager->playCurrent();
	}

	if  ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && this->choice <= SettingSelection::EFFECTSVOLUME) {//right
        switch (this->choice) {
            case SettingSelection::MASTERVOLUME:
                this->sys->soundManager->incrementGlobalVolume();
                break;
            case SettingSelection::MUSICVOLUME:
                this->sys->soundManager->incrementMusicVolume();
                break;
            case SettingSelection::EFFECTSVOLUME:
                this->sys->soundManager->incrementSfxVolume();
                break;
            default:
                break;
        }
	}

	if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && this->choice <= SettingSelection::EFFECTSVOLUME) {//left
        switch (this->choice) {
            case SettingSelection::MASTERVOLUME:
                this->sys->soundManager->decrementGlobalVolume();
                break;
            case SettingSelection::MUSICVOLUME:
                this->sys->soundManager->decrementMusicVolume();
                break;
            case SettingSelection::EFFECTSVOLUME:
                this->sys->soundManager->decrementSfxVolume();
                break;
            default:
                break;
        }
	}

	if (IsKeyPressed(KEY_ENTER) && this->choice == SettingSelection::RESET)  {//enter
	    this->sys->soundManager->resetVolume();

		/* } else if (*choice == 40 + settingsOpt) {//exit
			*choice = pause;//back to prew/paused choice
		} */
	}
}
