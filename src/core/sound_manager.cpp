#include <raylib.h>
#include "sound_manager.hpp"


SoundManager::SoundManager(){
    InitAudioDevice();

    this->slash = LoadSound("./audio/slash.mp3");
    SetSoundVolume(slash, ((float) this->effects*((float) this->global/100)));
    this->lobbyMusic = LoadMusicStream("./audio/temp lobby8bit.mp3");
	this->survivalMusic = LoadMusicStream("./audio/temp survival8bit.mp3");
	this->duelMusic = LoadMusicStream("./audio/temp duel8bit.mp3");

    this->currentSound = this->slash;//use currentSound to play all the sound with adjusted volume
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));

    //music
    this->currentMusic = this->lobbyMusic;//use currentMusic to play all the music with adjusted volume
    this->currentMusic.looping = true;

    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
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
    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
}

void SoundManager::setMusic(float level){
    this->music = level;
    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
}

void SoundManager::setSFX(float level){
    this->effects = level;
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
}


void SoundManager::incrementGlobalVolume(){
    this->global = (this->global+5>=100) ? 100 : this->global+5;

    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
}
void SoundManager::incrementMusicVolume(){
    this->music = (this->music+5>=100) ? 100 : this->music+5;
    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
}
void SoundManager::incrementSfxVolume(){
    this->effects = (this->effects+5>=100) ? 100 : this->effects+5;
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
}

void SoundManager::decrementGlobalVolume(){
    this->global = (this->global-5 <= 0) ? 0 : this->global-5;

    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
}
void SoundManager::decrementMusicVolume(){
    this->music = (this->music-5 <= 0) ? 0 : this->music-5;
    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
}
void SoundManager::decrementSfxVolume(){
    this->effects = (this->effects-5 <= 0) ? 0 : this->effects-5;
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
}

void SoundManager::resetVolume(){
    this->global= 75.0;
    this->effects= 70.0;
    this->music= 50.0;

    SetMusicVolume(this->currentMusic, ((float) this->music / 100) * ((float) this->global / 100));
    SetSoundVolume(this->currentSound, ((float) this->effects / 100) * ((float) this->global / 100));
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
