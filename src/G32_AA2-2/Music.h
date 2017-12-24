#pragma once

#include <SDL_mixer.h>
#include <unordered_map>
#include "Constants.h"

class Music {
private:
	std::unordered_map<std::string, Mix_Music*> soundtracks;
public:
	Music();
	~Music();
	void AddSoundtrack(std::string id, std::string path);
	void Play(std::string id);
	void Stop();
};