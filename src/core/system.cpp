// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include "modality.hpp"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <raylib.h>

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

int System::getFPS() {
    return fps;
}

bool System::shouldExit() { // alt + Kirk -> shot program
    return shutdown || (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_K));
}

System::System(){
    shutdown = false;

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    rng.seed(milliseconds);

    icon = LoadImage("./textures/temp donut.png");

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

    // render = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);

    fps = DEF_FPS;
    SetTargetFPS(fps);

    soundManager = SoundManager::getInstance();

    modalityType= ModalityType::NONE; // useful?
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

    SetWindowSize(DEF_WIDTH, DEF_HEIGHT);
    SetWindowPosition( // center
        monitorWidth/2 - (float)DEF_WIDTH/2,
        monitorHeight/2 - (float)DEF_HEIGHT/2
    );

    updateScreenSizeWH(); // update only
}

 void System::resizeWindowByWidth(int width) {
     float w = std::max( width, MIN_WIDTH);

     SetWindowSize(
         w,
         (w*9)/16 // mantain aspect ratio 16:9
     );

     updateScreenSizeWH(); // update only
 }

 DisplayMode System::getDisplayMode() {
     if(borderlessWindow) return DisplayMode::BORDERLESS_WINDOW;
     if(IsWindowFullscreen()) return DisplayMode::FULLSCREEN;

     return DisplayMode::RESIZABLE_WINDOW;
 }

 void System::update() {
     updateScreenSizeWH(); // update only
 }
