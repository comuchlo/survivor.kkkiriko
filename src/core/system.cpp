// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include "modality.hpp"
#include <chrono>

System* System::instance = nullptr;

System* System::getInstance(){
    if (instance == nullptr){
            instance = new System();
    }
    return instance;
}

Vector2 System::getScreenSizeWH(){ // return aligns with the raylib standard
    this->screenHeight = GetScreenHeight();
    this->screenWidth = GetScreenWidth();
    return { this->screenWidth, this->screenHeight };
}

Vector2 System::getMonitorSizeWH(){
    this->monitorWidth = GetMonitorWidth(this->currMonitor);
    this->monitorHeight = GetMonitorHeight(this->currMonitor);
    return { this->monitorWidth, this->monitorHeight };
}

int System::getCurrentMonitor() {
    this->currMonitor = GetCurrentMonitor();
    return this->currMonitor;
}

Vector2 System::getRenderSizeWH() {
    return { (float)this->render.texture.width, (float)this->render.texture.height };
}

int System::getFPS() {
    if(this->fps <= 0) {
        this->fps = DEF_FPS;
        SetTargetFPS(this->fps);
    }
    return fps;
}

bool System::shouldExit() {
    return this->shutdown || (IsKeyPressed(KEY_LEFT_ALT) && IsKeyPressed(KEY_F4));
}

System::System(){
    this->shutdown = false;

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    this->rng.seed(milliseconds);

    this->icon = LoadImage("./textures/temp donut.png");

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(DEF_WIDTH, DEF_HEIGHT, "Kiriko and the donuts");
    SetWindowIcon(icon);

    this->getCurrentMonitor();// update only
    this->getMonitorSizeWH();// update only
    this->getScreenSizeWH();// update only

    this->render = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);

    this->getFPS();// update only
    this->soundManager = SoundManager::getInstance();

    this->modalityType= ModalityType::LOBBY;
    this->cec = ControllerExitCode::CONTINUE;
}

System::~System(){
    UnloadImage(this->icon);
    CloseWindow();
}
