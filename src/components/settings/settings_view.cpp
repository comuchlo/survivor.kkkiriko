#include <raylib.h>
#include "settings.hpp"


void Settings::drawSettings() { //: master volume , music volume , effects volume
    auto [screenWidth, screenHeight]= this->sys->getScreenSizeWH();
    // title
    this->drawer->drawTextSF("Settings", (screenWidth / 2) - (MeasureText("Settings", this->sys->titlefontSize) / 2), 50, this->sys->titlefontSize, RED, BLACK, BLACK);

    //Master Volume
	this->drawer->drawTextSF("Master Volume", (screenWidth / 2) - (MeasureText("Master Volume", this->sys->buttonFontSize) / 2), 250, this->sys->buttonFontSize, BLACK, BLACK, (this->choice == SettingSelection::MASTERVOLUME) ? RED : WHITE);

	int shiftDown = 0, volumeLevel;//shift down all below if smth is focussed & lvl in px of certain volume

	if (this->choice == SettingSelection::MASTERVOLUME) {//Master Volume range bar if MasterVolume is focussed
		shiftDown = 60;
    this->drawer->drawRangeBar(this->soundMan->getGlobalLvl(), 303);
	}

	//Music Volume
	this->drawer->drawTextSF("Music Volume", (screenWidth / 2) - (MeasureText("Music Volume", this->sys->buttonFontSize) / 2), 310 + shiftDown, this->sys->buttonFontSize, BLACK, BLACK, (this->choice == SettingSelection::MUSICVOLUME) ? RED : WHITE);

	if (this->choice == SettingSelection::MUSICVOLUME) {//Music Volume range bar if MusicVolume is focussed
		shiftDown = 60;
		this->drawer->drawRangeBar(this->soundMan->getMusicLvl(), 363);
	}

	//Effects Volume
	this->drawer->drawTextSF("Effects Volume", (screenWidth / 2) - (MeasureText("Effects Volume", this->sys->buttonFontSize) / 2), 370 + shiftDown, this->sys->buttonFontSize, BLACK, BLACK, (this->choice == SettingSelection::EFFECTSVOLUME) ? RED : WHITE);

	if (this->choice == SettingSelection::EFFECTSVOLUME) {//Effects Volume range bar if EffectsVolume is focussed
		shiftDown = 60;
		this->drawer->drawRangeBar(this->soundMan->getSfxLvl(), 423);
	}

	//reset the settings
	this->drawer->drawTextSF("Reset the Settings", (screenWidth / 2) - (MeasureText("Reset the Settings", this->sys->buttonFontSize) / 2), 430 + shiftDown, this->sys->buttonFontSize, BLACK, BLACK, (this->choice == SettingSelection::RESET) ? RED : WHITE);
	//Exit
	this->drawer->drawTextSF("Exit", ( screenWidth / 2) - (MeasureText("Exit", this->sys->buttonFontSize) / 2), 490 + shiftDown, this->sys->buttonFontSize, BLACK, BLACK, (this->choice == SettingSelection::EXIT) ? RED : WHITE);
}
