// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include "modality.hpp"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <raylib.h>

DisplayMode& operator++(DisplayMode& val) {
    if (val == DisplayMode::BORDERLESS_WINDOW){
        val = DisplayMode::RESIZABLE_WINDOW;
    }else{
        val = static_cast<DisplayMode>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

DisplayMode operator++(DisplayMode& val, int) {
  DisplayMode oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

DisplayMode& operator--(DisplayMode& val) {
    if (val == DisplayMode::RESIZABLE_WINDOW){
        val = DisplayMode::BORDERLESS_WINDOW;
    }else{
        val = static_cast<DisplayMode>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

DisplayMode operator--(DisplayMode& val, int) {
  DisplayMode oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

System* System::instance = nullptr;

System* System::getInstance(){
    if (instance == nullptr){
        instance = new System();
    }
    return instance;
}

Vector2 System::getScreenSizeWH(){ // return aligns with the raylib standard
    return { screenWidth, screenHeight };
}

void System::updateScreenSizeWH() {
    screenHeight = GetScreenHeight();
    screenWidth = GetScreenWidth();
}

Vector2 System::getMonitorSizeWH(){
    return { monitorWidth, monitorHeight };
}

void System::updateMonitorSizeWH() {
    monitorWidth = GetMonitorWidth(currMonitor);
    monitorHeight = GetMonitorHeight(currMonitor);
}

int System::getCurrentMonitor() {
    return currMonitor;
}

void System::updateCurrentMonitor() {
    currMonitor = GetCurrentMonitor();
}

// Vector2 System::getRenderSizeWH() {
//     return { RENDER_WIDTH, RENDER_HEIGHT };
// }

unsigned int System::getFPS() {
    return fps;
}

unsigned int System::getCurrentFPS() {
    return GetFPS();
}

void System::incrementFPS() {
    fps += DELTA_FPS;

    if(fps > MAX_FPS) {
        fps = MIN_FPS;
    } else if(fps < MIN_FPS) {
        fps = MAX_FPS;
    }

    SetTargetFPS(fps);
}
void System::decrementFPS() {
    fps -= DELTA_FPS;

    if(fps > MAX_FPS) {
        fps = MIN_FPS;
    } else if(fps < MIN_FPS) {
        fps = MAX_FPS;
    }

    SetTargetFPS(fps);
}

bool System::isVsyncOn() {
    return IsWindowState(FLAG_VSYNC_HINT);
}

void System::toggleVsync() {
    if(isVsyncOn())
        ClearWindowState(FLAG_VSYNC_HINT);
    else
        SetWindowState(FLAG_VSYNC_HINT);
}

bool System::shouldExit() { // alt + Kirk -> shot program
    return shutdown || (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_K)) || WindowShouldClose();
}

System::System(){
    shutdown = false;

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    rng.seed(milliseconds);

    icon = LoadImage("./textures/donut.png");

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(DEF_WIDTH, DEF_HEIGHT, "Kiriko and the donuts");
    SetExitKey(KEY_NULL);
    SetWindowIcon(icon);

    SetWindowMinSize(MIN_WIDTH, MIN_HEIGHT);

    updateCurrentMonitor();// update only
    updateMonitorSizeWH();// update only
    updateScreenSizeWH();// update only

    SetWindowPosition( // center
        monitorWidth/2 - screenWidth/2,
        monitorHeight/2 - screenHeight/2
    );

    borderlessWindow = false;

    // note: if V-SYNC works properly, SetTargetFPS may be able to only lower the FPS
    // here SetTargetFPS is a fallback if V-SYNC is not supported
    fps = DEF_FPS;
    SetTargetFPS(fps);

    soundManager = SoundManager::getInstance();

    modalityType= ModalityType::NONE; // useful? // no ma è baka, pwe capirsi, credo
}

System::~System(){
    UnloadImage(icon);
    CloseWindow();
}

void System::shutDown() {
    shutdown = true;
}

void System::setFullScreen() {
    if(IsWindowFullscreen()) return;

    // important: make sure to not be on borderlessWindow when toggle fullscreen
    if(borderlessWindow) {
        ToggleBorderlessWindowed();
        borderlessWindow = false;
    }

    ToggleFullscreen();

    updateScreenSizeWH(); // update only
}

void System::setBorderlessWindow() {
    if(borderlessWindow) return;

    // important: make sure to not be on fullscreen when toggle borderless window
    if(IsWindowFullscreen()) ToggleFullscreen();

    ToggleBorderlessWindowed();
    borderlessWindow = true;

    updateScreenSizeWH(); // update only
}

void System::minimizeWindow() {
    if(IsWindowFullscreen()) {
        ToggleFullscreen();
    }
    if(borderlessWindow) {
        ToggleBorderlessWindowed();
        borderlessWindow = false;
    }

    SetWindowSize(MIN_WIDTH, MIN_HEIGHT);

    updateScreenSizeWH(); // update only
}

void System::maximizeWindow() {
    if(IsWindowFullscreen()) {
        ToggleFullscreen();
    }
    if(borderlessWindow) {
        ToggleBorderlessWindowed();
        borderlessWindow = false;
    }

    SetWindowPosition(0, 0);
    SetWindowSize(monitorWidth, monitorHeight);

    updateScreenSizeWH(); // update only
}

void System::resetWindow() {
    if(IsWindowFullscreen()) {
        ToggleFullscreen();
    }
    if(borderlessWindow) {
        ToggleBorderlessWindowed();
        borderlessWindow = false;
    }

    RestoreWindow();

    SetWindowSize(DEF_WIDTH, DEF_HEIGHT);
    SetWindowPosition( // center
        monitorWidth/2 - (float)DEF_WIDTH/2,
        monitorHeight/2 - (float)DEF_HEIGHT/2
    );

    updateScreenSizeWH(); // update only
}

void System::resetVideo() {
    resetWindow();

    fps = DEF_FPS;
    SetTargetFPS(fps);

    if(!isVsyncOn()) toggleVsync();

}

 void System::resizeWindowByWidth(int width) {
     float w = std::clamp(width, MIN_WIDTH, (int)(getMonitorSizeWH().x));

     RestoreWindow();

     SetWindowSize(
         w,
         (w*9)/16 // mantain aspect ratio 16:9
     );

     updateScreenSizeWH(); // update only
 }

 DisplayMode System::getDisplayMode() {
     if(borderlessWindow) {
         return DisplayMode::BORDERLESS_WINDOW;
     }
     if(IsWindowFullscreen()) {
         return DisplayMode::FULLSCREEN;
     }

     return DisplayMode::RESIZABLE_WINDOW;
 }

 void System::update() {
     updateScreenSizeWH(); // update only
 }
