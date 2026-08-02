#include <raylib.h>
#include "sound_manager.hpp"


SoundManager::SoundManager(){
    InitAudioDevice();

    this->slash = LoadSound("./audio/slash.mp3");
    SetSoundVolume(slash, (this->effects * (this->global/100.0f)));
    this->lobbyMusic = LoadMusicStream("./audio/temp lobby8bit.mp3");
	this->survivalMusic = LoadMusicStream("./audio/temp survival8bit.mp3");
	this->duelMusic = LoadMusicStream("./audio/temp duel8bit.mp3");

    this->currentSound = this->slash;//use currentSound to play all the sound with adjusted volume
    SetSoundVolume(this->currentSound, (this->effects / 100.0f) * (this->global / 100.0f));

    //music
    this->currentMusic = this->lobbyMusic;//use currentMusic to play all the music with adjusted volume
    this->currentMusic.looping = true;

    SetMusicVolume(this->currentMusic, (this->music / 100.0f) * (this->global / 100.0f));
    PlayMusicStream(this->currentMusic);
}


SoundManager* SoundManager::getInstance(){
    if (instance == nullptr){
            instance = new SoundManager();
    }
    return instance;
}

SoundManager::~SoundManager(){
    UnloadSound(this->slash);

    UnloadMusicStream(this->lobbyMusic);
    UnloadMusicStream(this->duelMusic);
    UnloadMusicStream(this->survivalMusic);

    CloseAudioDevice();
}

void SoundManager::setGlobal(float level){
    this->global = level;
    SetMusicVolume(this->currentMusic, ( (this->music / 100.0f) * (this->global / 100.0f)));
    SetSoundVolume(this->currentSound, ( (this->effects / 100.0f) * (this->global / 100.0f)));
}

void SoundManager::setMusic(float level){
    this->music = level;
    SetMusicVolume(this->currentMusic, ((this->music / 100.0f) * (this->global / 100.0f)));
}

void SoundManager::setSFX(float level){
    this->effects = level;
    SetSoundVolume(this->currentSound, ((this->effects / 100.0f) * (this->global / 100.0f)));
}


void SoundManager::incrementGlobalVolume(){
    this->global = (this->global+5.0f>=100.0f) ? 100.0f : this->global+5.0f;

    SetMusicVolume(this->currentMusic, ( this->music / 100.0f) * ( this->global / 100.0f));
    SetSoundVolume(this->currentSound, ( this->effects / 100.0f) * ( this->global / 100.0f));
}
void SoundManager::incrementMusicVolume(){
    this->music = (this->music+5.0f>=100.0f) ? 100.0f : this->music+5.0f;
    SetMusicVolume(this->currentMusic, ( this->music / 100.0f) * ( this->global / 100.0f));
}
void SoundManager::incrementSfxVolume(){
    this->effects = (this->effects+5.0f>=100.0f) ? 100.0f : this->effects+5.0f;
    SetSoundVolume(this->currentSound, ( this->effects / 100.0f) * ( this->global / 100.0f));
}

void SoundManager::decrementGlobalVolume(){
    this->global = (this->global-5.0f <= 0.0f) ? 0.0f : this->global-5.0f;

    SetMusicVolume(this->currentMusic, (this->music / 100.0f) * (this->global / 100.0f));
    SetSoundVolume(this->currentSound, (this->effects / 100.0f) * (this->global / 100.0f));
}
void SoundManager::decrementMusicVolume(){
    this->music = (this->music-5.0f <= 0.0f) ? 0.0f : this->music-5.0f;
    SetMusicVolume(this->currentMusic, (this->music / 100.0f) * (this->global / 100.0f));
}
void SoundManager::decrementSfxVolume(){
    this->effects = (this->effects-5.0f <= 0.0f) ? 0.0f : this->effects-5.0f;
    SetSoundVolume(this->currentSound, (this->effects / 100.0f) * (this->global / 100.0f));
}

void SoundManager::resetVolume(){
    this->global= 75.0f;
    this->effects= 70.0f;
    this->music= 50.0f;

    SetMusicVolume(this->currentMusic, (this->music / 100.0f) * (this->global / 100.0f));
    SetSoundVolume(this->currentSound, (this->effects / 100.0f) * (this->global / 100.0f));
}

float SoundManager::getGlobalLvl(){
    return this->global;
}
float SoundManager::getMusicLvl(){
    return this->music;
}
float SoundManager::getSfxLvl(){
    return this->effects;
}

void SoundManager::playCurrent(){
    PlaySound(this->currentSound);
}
