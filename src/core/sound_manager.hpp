#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <raylib.h>

class SoundManager {
    private:
        static constexpr float DEF_GLOBAL_LVL = 0.5f, DEF_EFFECTS_LVL = 0.7f,
            DEF_MUSIC_LVL = 0.5f, DELTA_LVL = 0.05f;

        static SoundManager* instance;

        float global = DEF_GLOBAL_LVL;
        float effects = DEF_EFFECTS_LVL;
        float music = DEF_MUSIC_LVL;
        Music currentMusic, lobbyMusic, survivalMusic, duelMusic;
        Sound currentSound, slash;

        SoundManager();
    public:
        ~SoundManager();
        SoundManager(const SoundManager&) = delete;
        SoundManager& operator=(const SoundManager&) = delete;
        static SoundManager* getInstance();

        // void setGlobal(float);
        // void setSFX(float);
        // void setMusic(float);

        void incrementGlobalVolume();
        void incrementMusicVolume();
        void incrementSfxVolume();

        void decrementGlobalVolume();
        void decrementMusicVolume();
        void decrementSfxVolume();

        void resetVolume();

        float getGlobalLvl();
        float getMusicLvl();
        float getSfxLvl();

        void playCurrent();

        void updateAudio();
};

#endif
