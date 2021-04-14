#include "sound/Sound.hpp"


bool Sound::init() {
    if(isInit)
        return true;
    //initialize SDL mixer
    else {
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        std::cerr << "Error while initializing SDL" << std::endl;
        exit(1);
    }

    std::string path = "assets/sound/tetris_sound.wav";
    snd=Mix_LoadWAV(path.c_str());

    isInit = true;
    std::cout << "Sounds loaded successfully" << std::endl;
    }  
    return true;
}

void Sound::play(int i, bool looped ){
    looped = 0;
    
    if ( !isInit ) return;
    if (!on) return;

    if (Mix_Playing(i))
        Mix_HaltChannel(i);

    int loop = 0;
    if ( looped )
        loop = -1;

    Mix_PlayChannel(-1,snd,loop);

}

Sound::Sound(std::string path) : on(true) , isInit(false) {
    path = "assets/sound/tetris_sound.mp3";
}

Sound::~Sound() { 
    Mix_CloseAudio();
}