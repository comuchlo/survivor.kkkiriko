#include "settings.hpp"
#include <cstdio>
#include <cstring>


void Settings::drawModality() { //: master volume , music volume , effects volume
    char tempbuffer[60];
    const DisplayMode dm = sys->getDisplayMode();
    const auto [screenW, screenH] = sys->getScreenSizeWH();
    const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize, textFont = drawer->textFontSize;


    // background image
    DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image

    // title
    drawer->drawTextSFC("Settings", 50, titleFont, RED, BLACK, BLACK);

    //Master Volume
	drawer->drawTextSFC("Master Volume", 250, buttonFont, BLACK, BLACK, (choice == SettingSelection::MASTERVOLUME) ? RED : WHITE);

	int shiftDown = 0, volumeLevel;//shift down all below if smth is focussed & lvl in px of certain volume

	if (choice == SettingSelection::MASTERVOLUME) {//Master Volume range bar if MasterVolume is focussed
		shiftDown = 60;
		drawer->drawRangeBar(sys->soundManager->getGlobalLvl(), 303);
	}

	//Music Volume
	drawer->drawTextSFC("Music Volume", 310 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::MUSICVOLUME) ? RED : WHITE);

	if (choice == SettingSelection::MUSICVOLUME) {//Music Volume range bar if MusicVolume is focussed
		shiftDown = 60;
		drawer->drawRangeBar(sys->soundManager->getMusicLvl(), 363);
	}

	//Effects Volume
	drawer->drawTextSFC("Effects Volume", 370 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::EFFECTSVOLUME) ? RED : WHITE);

	if (choice == SettingSelection::EFFECTSVOLUME) {//Effects Volume range bar if EffectsVolume is focussed
		shiftDown = 60;
		drawer->drawRangeBar(sys->soundManager->getSfxLvl(), 423);
	}

	//reset the settings
	drawer->drawTextSFC("Reset audio Settings", 430 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESETAUDIO) ? RED : WHITE);

	// display mode
	drawer->drawTextSFC("Display Mode", 490 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

	if(choice == SettingSelection::DISPLAYMODE) {
    shiftDown = 60;
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
    	drawer->drawTextSFC(tempbuffer, 543, textFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

	    drawer->drawArrowSF((renderWidth / 2) - (drawer->measureText(tempbuffer, textFont) / 2) - 15 - textFont, 543, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
        drawer->drawArrowSF((renderWidth / 2) + (drawer->measureText(tempbuffer, textFont) / 2) + 15, 543, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);
	}

	//resolution
	drawer->drawTextSFC("Resolution", 550 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);

	if(choice == SettingSelection::RESOLUTION) {
	    shiftDown = 60;
	    sprintf(tempbuffer, "%.0f x %.0f", screenW, screenH);
        drawer->drawTextSFC(tempbuffer, 603, textFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);
        if(dm == DisplayMode::RESIZABLE_WINDOW) {
            drawer->drawArrowSF((renderWidth / 2) - (drawer->measureText(tempbuffer, textFont) / 2) - 15 - textFont, 603, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
            drawer->drawArrowSF((renderWidth / 2) + (drawer->measureText(tempbuffer, textFont) / 2) + 15, 603, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);
        }
	}

	//fps
	drawer->drawTextSFC("FPS", 610 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::FPS) ? RED : WHITE);

	if(choice == SettingSelection::FPS) {
        shiftDown = 100;

	    // max fps
		const unsigned int tempFPS = sys->getFPS();
		if(tempFPS == 0) {
		    strcpy(tempbuffer, "maximum: uncapped");
	    } else {
			sprintf(tempbuffer, "maximum: %d", sys->getFPS());
		}
        drawer->drawTextSFC(tempbuffer, 663, textFont, BLACK, BLACK, RED);
        drawer->drawArrowSF((renderWidth / 2) - (drawer->measureText(tempbuffer, textFont) / 2) - 15 - textFont, 663, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
        drawer->drawArrowSF((renderWidth / 2) + (drawer->measureText(tempbuffer, textFont) / 2) + 15, 663, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);

        // current fps
        sprintf(tempbuffer, "current: %d", sys->getCurrentFPS());
        drawer->drawTextSFC(tempbuffer, 698, textFont, BLACK, BLACK, RED);

	}

	// vsync
	drawer->drawTextSFC("V-SYNC", 670 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::VSYNC) ? RED : WHITE);

	if(choice == SettingSelection::VSYNC) {
        shiftDown = 60;
        strcpy(tempbuffer, (sys->isVsyncOn()) ? "ON" : "OFF");
        drawer->drawTextSFC(tempbuffer, 723, textFont, BLACK, BLACK, RED);
        drawer->drawArrowSF((renderWidth / 2) - (drawer->measureText(tempbuffer, textFont) / 2) - 15 - textFont, 723, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
        drawer->drawArrowSF((renderWidth / 2) + (drawer->measureText(tempbuffer, textFont) / 2) + 15, 723, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);

	}

	//reset video
	drawer->drawTextSFC("Reset Video", 730 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESETVIDEO) ? RED : WHITE);

	//Exit
	drawer->drawTextSFC("Exit", 790 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::EXIT) ? RED : WHITE);

// 	// title
//     drawer->drawTextSF("Settings", (renderWidth / 2) - ((float)MeasureText("Settings", sys->titlefontSize) / 2), 50, sys->titlefontSize, RED, BLACK, BLACK);

//     //Master Volume
// drawer->drawTextSF("Master Volume", (renderWidth / 2) - ((float)MeasureText("Master Volume", sys->buttonFontSize) / 2), 250, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::MASTERVOLUME) ? RED : WHITE);

// int shiftDown = 0, volumeLevel;//shift down all below if smth is focussed & lvl in px of certain volume

// if (choice == SettingSelection::MASTERVOLUME) {//Master Volume range bar if MasterVolume is focussed
// shiftDown = 60;
//     drawer->drawRangeBar(sys->soundManager->getGlobalLvl(), 303);
// }

// //Music Volume
// drawer->drawTextSF("Music Volume", (renderWidth / 2) - ((float)MeasureText("Music Volume", sys->buttonFontSize) / 2), 310 + shiftDown, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::MUSICVOLUME) ? RED : WHITE);

// if (choice == SettingSelection::MUSICVOLUME) {//Music Volume range bar if MusicVolume is focussed
// shiftDown = 60;
// drawer->drawRangeBar(sys->soundManager->getMusicLvl(), 363);
// }

// //Effects Volume
// drawer->drawTextSF("Effects Volume", (renderWidth / 2) - ((float)MeasureText("Effects Volume", sys->buttonFontSize) / 2), 370 + shiftDown, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::EFFECTSVOLUME) ? RED : WHITE);

// if (choice == SettingSelection::EFFECTSVOLUME) {//Effects Volume range bar if EffectsVolume is focussed
// shiftDown = 60;
// drawer->drawRangeBar(sys->soundManager->getSfxLvl(), 423);
// }

// //reset the settings
// drawer->drawTextSF("Reset audio Settings", (renderWidth / 2) - ((float)MeasureText("Reset audio Settings", sys->buttonFontSize) / 2), 430 + shiftDown, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::RESETAUDIO) ? RED : WHITE);

// // display mode
// drawer->drawTextSF("Display Mode", (renderWidth / 2) - ((float)MeasureText("Display Mode", buttonFont) / 2), 490 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

// if(choice == SettingSelection::DISPLAYMODE) {
//     shiftDown = 60;
//     	sprintf(
//     	    tempbuffer,
//     		"%s",
//     		(dm == DisplayMode::BORDERLESS_WINDOW) ?
//     		    "Borderless window" :
//     			((dm == DisplayMode::FULLSCREEN) ?
//     			    "Fullscreen" :
//     				"Resizable window"
//     			)
//     	);
//     	drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 543, textFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

//   drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 543, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//         drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 543, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);
// }

// //resolution
// drawer->drawTextSF("Resolution", (renderWidth / 2) - ((float)MeasureText("Resolution", sys->buttonFontSize) / 2), 550 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);

// if(choice == SettingSelection::RESOLUTION) {
//   shiftDown = 60;
//   sprintf(tempbuffer, "%.0f x %.0f", screenW, screenH);
//         drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 603, textFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);
//         if(dm == DisplayMode::RESIZABLE_WINDOW) {
//             drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 603, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//             drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 603, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);
//         }
// }

// //fps
// drawer->drawTextSF("FPS", (renderWidth / 2) - ((float)MeasureText("FPS", buttonFont) / 2), 610 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::FPS) ? RED : WHITE);

// if(choice == SettingSelection::FPS) {
//         shiftDown = 100;

//   // max fps
// const unsigned int tempFPS = sys->getFPS();
// if(tempFPS == 0) {
//    strcpy(tempbuffer, "maximum: uncapped");
//   } else {
// sprintf(tempbuffer, "maximum: %d", sys->getFPS());
// }
//         drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 663, textFont, BLACK, BLACK, RED);
//         drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 663, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//         drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 663, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);

//         // current fps
//         sprintf(tempbuffer, "current: %d", sys->getCurrentFPS());
//         drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 698, textFont, BLACK, BLACK, RED);

// }

// // vsync
// drawer->drawTextSF("V-SYNC", (renderWidth / 2) - ((float)MeasureText("V-SYNC", buttonFont) / 2), 670 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::VSYNC) ? RED : WHITE);

// if(choice == SettingSelection::VSYNC) {
//         shiftDown = 60;
//         strcpy(tempbuffer, (sys->isVsyncOn()) ? "ON" : "OFF");
//         drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 723, textFont, BLACK, BLACK, RED);// title
//             drawer->drawTextSF("Settings", (renderWidth / 2) - ((float)MeasureText("Settings", sys->titlefontSize) / 2), 50, sys->titlefontSize, RED, BLACK, BLACK);

//             //Master Volume
// 	drawer->drawTextSF("Master Volume", (renderWidth / 2) - ((float)MeasureText("Master Volume", sys->buttonFontSize) / 2), 250, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::MASTERVOLUME) ? RED : WHITE);

// 	int shiftDown = 0, volumeLevel;//shift down all below if smth is focussed & lvl in px of certain volume

// 	if (choice == SettingSelection::MASTERVOLUME) {//Master Volume range bar if MasterVolume is focussed
// 		shiftDown = 60;
//             drawer->drawRangeBar(sys->soundManager->getGlobalLvl(), 303);
// 	}

// 	//Music Volume
// 	drawer->drawTextSF("Music Volume", (renderWidth / 2) - ((float)MeasureText("Music Volume", sys->buttonFontSize) / 2), 310 + shiftDown, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::MUSICVOLUME) ? RED : WHITE);

// 	if (choice == SettingSelection::MUSICVOLUME) {//Music Volume range bar if MusicVolume is focussed
// 		shiftDown = 60;
// 		drawer->drawRangeBar(sys->soundManager->getMusicLvl(), 363);
// 	}

// 	//Effects Volume
// 	drawer->drawTextSF("Effects Volume", (renderWidth / 2) - ((float)MeasureText("Effects Volume", sys->buttonFontSize) / 2), 370 + shiftDown, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::EFFECTSVOLUME) ? RED : WHITE);

// 	if (choice == SettingSelection::EFFECTSVOLUME) {//Effects Volume range bar if EffectsVolume is focussed
// 		shiftDown = 60;
// 		drawer->drawRangeBar(sys->soundManager->getSfxLvl(), 423);
// 	}

// 	//reset the settings
// 	drawer->drawTextSF("Reset audio Settings", (renderWidth / 2) - ((float)MeasureText("Reset audio Settings", sys->buttonFontSize) / 2), 430 + shiftDown, sys->buttonFontSize, BLACK, BLACK, (choice == SettingSelection::RESETAUDIO) ? RED : WHITE);

// 	// display mode
// 	drawer->drawTextSF("Display Mode", (renderWidth / 2) - ((float)MeasureText("Display Mode", buttonFont) / 2), 490 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

// 	if(choice == SettingSelection::DISPLAYMODE) {
//             shiftDown = 60;
//             	sprintf(
//             	    tempbuffer,
//             		"%s",
//             		(dm == DisplayMode::BORDERLESS_WINDOW) ?
//             		    "Borderless window" :
//             			((dm == DisplayMode::FULLSCREEN) ?
//             			    "Fullscreen" :
//             				"Resizable window"
//             			)
//             	);
//             	drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 543, textFont, BLACK, BLACK, (choice == SettingSelection::DISPLAYMODE) ? RED : WHITE);

// 	    drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 543, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//                 drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 543, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);
// 	}

// 	//resolution
// 	drawer->drawTextSF("Resolution", (renderWidth / 2) - ((float)MeasureText("Resolution", sys->buttonFontSize) / 2), 550 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);

// 	if(choice == SettingSelection::RESOLUTION) {
// 	    shiftDown = 60;
// 	    sprintf(tempbuffer, "%.0f x %.0f", screenW, screenH);
//                 drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 603, textFont, BLACK, BLACK, (choice == SettingSelection::RESOLUTION) ? RED : WHITE);
//                 if(dm == DisplayMode::RESIZABLE_WINDOW) {
//                     drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 603, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//                     drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 603, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);
//                 }
// 	}

// 	//fps
// 	drawer->drawTextSF("FPS", (renderWidth / 2) - ((float)MeasureText("FPS", buttonFont) / 2), 610 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::FPS) ? RED : WHITE);

// 	if(choice == SettingSelection::FPS) {
//                 shiftDown = 100;

// 	    // max fps
// 		const unsigned int tempFPS = sys->getFPS();
// 		if(tempFPS == 0) {
// 		    strcpy(tempbuffer, "maximum: uncapped");
// 	    } else {
// 			sprintf(tempbuffer, "maximum: %d", sys->getFPS());
// 		}
//                 drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 663, textFont, BLACK, BLACK, RED);
//                 drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 663, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//                 drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 663, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);

//                 // current fps
//                 sprintf(tempbuffer, "current: %d", sys->getCurrentFPS());
//                 drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 698, textFont, BLACK, BLACK, RED);

// 	}

// 	// vsync
// 	drawer->drawTextSF("V-SYNC", (renderWidth / 2) - ((float)MeasureText("V-SYNC", buttonFont) / 2), 670 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::VSYNC) ? RED : WHITE);

// 	if(choice == SettingSelection::VSYNC) {
//                 shiftDown = 60;
//                 strcpy(tempbuffer, (sys->isVsyncOn()) ? "ON" : "OFF");
//                 drawer->drawTextSF(tempbuffer, (renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2), 723, textFont, BLACK, BLACK, RED);
//                 drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 723, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//                 drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 723, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);

// 	}

// 	//reset video
// 	drawer->drawTextSF("Reset Video", (renderWidth / 2) - ((float)MeasureText("Reset Video", buttonFont) / 2), 730 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESETVIDEO) ? RED : WHITE);

// 	//Exit
// 	drawer->drawTextSF("Exit", ( renderWidth / 2) - ((float)MeasureText("Exit", sys->buttonFontSize) / 2), 790 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::EXIT) ? RED : WHITE);
//         drawer->drawArrowSF((renderWidth / 2) - ((float)MeasureText(tempbuffer, textFont) / 2) - 15 - textFont, 723, textFont, textFont, 3.0f, true, BLACK, BLACK, RED);
//         drawer->drawArrowSF((renderWidth / 2) + ((float)MeasureText(tempbuffer, textFont) / 2) + 15, 723, textFont, textFont, 3.0f, false, BLACK, BLACK, RED);

// }

// //reset video
// drawer->drawTextSF("Reset Video", (renderWidth / 2) - ((float)MeasureText("Reset Video", buttonFont) / 2), 730 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::RESETVIDEO) ? RED : WHITE);

// //Exit
// drawer->drawTextSF("Exit", ( renderWidth / 2) - ((float)MeasureText("Exit", sys->buttonFontSize) / 2), 790 + shiftDown, buttonFont, BLACK, BLACK, (choice == SettingSelection::EXIT) ? RED : WHITE);
}
