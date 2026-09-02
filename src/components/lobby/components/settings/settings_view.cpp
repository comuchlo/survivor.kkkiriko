#include "settings.hpp"
#include <cstdio>
#include <cstring>
#include <raylib.h>


void Settings::drawModality() { //: master volume , music volume , effects volume
    const DisplayMode dm = sys->getDisplayMode();
    const auto [screenW, screenH] = sys->getScreenSizeWH();
    const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize, textFont = drawer->textFontSize;

    const int arrowPadding = 15; // distance between arrow and text for drawTextSFCA
    const float arrowThickness = 3.0f; // arrow thickness for drawTextSFCA

    char tempbuffer[60];
    int currH = 50; // for draw calls height

    // background image
    DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image

    // title
    drawer->drawTextSFC("Settings", currH, titleFont, RED, BLACK, BLACK);

    //Master Volume
    currH+= 200;
	drawer->drawTextSFC("Master Volume", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::MASTERVOLUME) ? RED : WHITE);

	if (choice == SettingSelection::MASTERVOLUME) {//Master Volume range bar if MasterVolume is focussed
		currH+= 53;
		drawer->drawRangeBar(sys->soundManager->getGlobalLvl(), 303);
	}

	//Music Volume
	currH+= 60;
	drawer->drawTextSFC("Music Volume", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::MUSICVOLUME) ? RED : WHITE);

	if (choice == SettingSelection::MUSICVOLUME) {//Music Volume range bar if MusicVolume is focussed
		currH+= 53;
		drawer->drawRangeBar(sys->soundManager->getMusicLvl(), currH);
	}

	//Effects Volume
	currH+= 60;
	drawer->drawTextSFC("Effects Volume", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::EFFECTSVOLUME) ? RED : WHITE);

	if (choice == SettingSelection::EFFECTSVOLUME) {//Effects Volume range bar if EffectsVolume is focussed
		currH+= 53;
		drawer->drawRangeBar(sys->soundManager->getSfxLvl(), currH);
	}

	//reset the settings
	currH+= 60;
	drawer->drawTextSFC("Reset audio Settings", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESETAUDIO) ? RED : WHITE);

	// display mode
	currH+= 60;
	drawer->drawTextSFC("Display Mode", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

	if(choice == SettingSelection::DISPLAYMODE) {
        currH+= 53;

    	sprintf(
    	    tempbuffer,
    		"%s",
    		(dm == DisplayMode::BORDERLESS_WINDOW) ?
    		    "Borderless window" :
    			((dm == DisplayMode::FULLSCREEN) ?
    			    "Fullscreen" :
    				"Resizable window"
    			)
    	);

        drawer->drawTextSFCA(tempbuffer, currH, textFont, true, arrowPadding, arrowThickness, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);
	}

	//resolution
	currH+= 60;
	drawer->drawTextSFC("Resolution", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);

	if(choice == SettingSelection::RESOLUTION) {
		currH+= 53;
	    sprintf(tempbuffer, "%.0f x %.0f", screenW, screenH);
		drawer->drawTextSFCA(tempbuffer, currH, textFont, dm == DisplayMode::RESIZABLE_WINDOW, arrowPadding, arrowThickness, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);
	}

	//fps
	currH+= 60;
	drawer->drawTextSFC("FPS", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::FPS) ? RED : WHITE);

	if(choice == SettingSelection::FPS) {
        currH+= 53;

	    // max fps
		const unsigned int tempFPS = sys->getFPS();
		if(tempFPS == 0) {
		    strcpy(tempbuffer, "maximum: uncapped");
	    } else {
			sprintf(tempbuffer, "maximum: %d", sys->getFPS());
		}
		drawer->drawTextSFCA(tempbuffer, currH, textFont, true, arrowPadding, arrowThickness, BLACK, BLACK, RED);

        // current fps
        currH+= 35;
        sprintf(tempbuffer, "current: %d", sys->getCurrentFPS());
        drawer->drawTextSFC(tempbuffer, currH, textFont, BLACK, BLACK, RED);

	}

	// vsync
	currH+= 60;
	drawer->drawTextSFC("V-SYNC", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::VSYNC) ? RED : WHITE);

	if(choice == SettingSelection::VSYNC) {
        currH+= 53;
        strcpy(tempbuffer, (sys->isVsyncOn()) ? "ON" : "OFF");
        drawer->drawTextSFCA(tempbuffer, currH, textFont, true, arrowPadding, arrowThickness, BLACK, BLACK, RED);

	}

	//reset video
	currH+= 60;
	drawer->drawTextSFC("Reset Video", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESETVIDEO) ? RED : WHITE);

	//Exit
	currH+= 60;
	drawer->drawTextSFC("Exit", currH, buttonFont, BLACK, BLACK, (choice == SettingSelection::EXIT) ? RED : WHITE);
}
