#include "SoundFactory.h"

int SoundFactory::musicVolume = MIX_MAX_VOLUME;
int SoundFactory::soundVolume = MIX_MAX_VOLUME;

std::map<std::string, Mix_Music*> SoundFactory::musicData;
std::map<std::string, Mix_Chunk*> SoundFactory::chunkData;

void SoundFactory::initAUDIO()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
	}
	if (Mix_Init(MIX_INIT_MP3) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, Mix_GetError());
	}

	// Open Audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, Mix_GetError());
	}
}

void SoundFactory::playMusic(const char * file, int loops)
{
	std::string key = std::string(file);
	if (musicData.find(std::string(key)) != musicData.end())
	{
		Mix_PlayMusic(musicData.at(std::string(key)), loops);
	}
	else
	{
		std::string path = "audio/music/" + std::string(file);
		Mix_Music* track = Mix_LoadMUS(path.c_str());
		if (track == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, Mix_GetError());
		}
		else
		{
			musicData.insert(std::pair<std::string, Mix_Music*>(file, track));
			Mix_PlayMusic(track, loops);
		}
	}
}

bool SoundFactory::isMusicPlaying()
{
	return Mix_PlayingMusic();
}

void SoundFactory::setMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

int SoundFactory::getMusicVolume()
{
	return musicVolume;
}

void SoundFactory::pauseMusic()
{
	Mix_PauseMusic();
}

void SoundFactory::resumeMusic()
{
	Mix_ResumeMusic();
}

void SoundFactory::playSound(const char * file, int loops)
{
	playSound(file, -1, loops);
}

void SoundFactory::playSound(const char * file, int channel, int loops)
{
	std::string key = std::string(file);
	if (chunkData.find(std::string(key)) != chunkData.end())
	{
		Mix_PlayChannel(channel, chunkData.at(std::string(key)), loops);
	}
	else
	{
		std::string path = "audio/sound/" + std::string(file);
		Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
		if (sound == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, Mix_GetError());
		}
		else
		{
			chunkData.insert(std::pair<std::string, Mix_Chunk*>(file, sound));
			Mix_PlayChannel(channel, sound, loops);
		}
	}
}

void SoundFactory::setSoundVolume(int volume, int channel)
{
	Mix_Volume(channel, volume);
}

int SoundFactory::getSoundVolume()
{
	return soundVolume;
}

void SoundFactory::pauseSound(int channel)
{
	Mix_Pause(channel);
}

void SoundFactory::resumeSound(int channel)
{
	Mix_Resume(channel);
}

bool SoundFactory::isSoundPlaying(int channel)
{
	return Mix_Playing(channel);
}

void SoundFactory::setChannel(int channels)
{
	Mix_AllocateChannels(channels);
}

void SoundFactory::quit()
{
	for (std::map<std::string, Mix_Music*>::iterator it = musicData.begin(); it != musicData.end(); ++it)
	{
		Mix_FreeMusic(it->second);
		it->second = NULL;
	}
	for (std::map<std::string, Mix_Chunk*>::iterator it = chunkData.begin(); it != chunkData.end(); ++it)
	{
		Mix_FreeChunk(it->second);
		it->second = NULL;
	}

	int openedAudio = Mix_QuerySpec(NULL, NULL, NULL);
	for (int i = 0; i < openedAudio; i++)
	{
		Mix_CloseAudio();
	}

	Mix_Quit();
}
