#include "main/avocado-global.h"

#include "SdlMusic.h"

namespace avo {

AbstractFactory<SdlMusic> *SdlMusic::factory = new AbstractFactory<SdlMusic>;

SdlMusic::SdlMusic()
	: music(NULL)
{
}

SdlMusic::SdlMusic(const boost::filesystem::path &uri)
{
	music = Mix_LoadMUS(uri.c_str());

	if (!music) {
		throw std::runtime_error(
			"Mix_LoadMUS failed! SDL says, \"" + std::string(SDL_GetError()) + "\"."
		);
	}

	setUri(uri);
}

SdlMusic::~SdlMusic() {
	if (music) Mix_FreeMusic(music);
}

int SdlMusic::play(int loops) {
	return Mix_PlayMusic(music, loops);
}

void SdlMusic::fadeIn(int loops, int ms, int position) {
	AVOCADO_UNUSED(position);

	Mix_FadeInMusic(music, loops, ms);
}

void SdlMusic::fadeOut(int ms) {
	Mix_FadeOutMusic(ms);
}

void SdlMusic::setVolume(int volume) {
	Mix_VolumeMusic(volume);
}

int SdlMusic::volume() {
	return Mix_VolumeMusic(-1);
}

void SdlMusic::stop() {
	Mix_HaltMusic();
}

int SdlMusic::isPlaying() {
	return Mix_PlayingMusic();
}

}
