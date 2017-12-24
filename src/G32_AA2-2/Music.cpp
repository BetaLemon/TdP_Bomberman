#include "Music.h"
Music::Music() {

	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)& mixFlags)) throw "Error: SDL_mixer init";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable to initialize SDL_mixer audio systems";
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	//Mix_PlayMusic(soundtrack, -1);	// -1 per a un loop. 1 per a una vegada...
}

void Music::AddSoundtrack(std::string id, std::string path) {
	Mix_Music * mixM{ Mix_LoadMUS(path.c_str()) };
	if (!mixM) throw "Unable to load the Mix_Music soundtrack";
	soundtracks[id] = mixM;
}

void Music::Play(std::string id) {
	Mix_PlayMusic(soundtracks[id], -1);
}

void Music::Stop() {
	Mix_HaltChannel(-1);
}

Music::~Music() {
	//
	Mix_Quit();
}