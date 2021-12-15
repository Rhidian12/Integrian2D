#include "SDLAudioSystem.h"
#include "../Timer/Timer.h"
#include "../Logger/Logger.h"

#include <algorithm>
#include <SDL_mixer.h>

namespace Integrian2D
{
	SDLAudioSystem::SDLAudioSystem()
		: m_Sounds{}
		, m_Music{}
		, m_Channels{}
		, m_pCurrentPlayingMusic{}
		, m_SDLMixerMaxVolume{ 128 }
	{
		Mix_AllocateChannels(24);

		for (uint16_t i{}; i < Mix_AllocateChannels(-1); ++i)
			m_Channels.push_back(Channel{ i });
	}

	SDLAudioSystem::~SDLAudioSystem()
	{
		for (const SoundPair& soundPair : m_Sounds)
			Mix_FreeChunk(soundPair.second);

		for (const MusicPair& musicPair : m_Music)
			Mix_FreeMusic(musicPair.second);
	}

	AudioSystem::SoundID SDLAudioSystem::AddSound(const std::string& filePath)
	{
		SoundID newSoundID{};

		if (m_Sounds.empty())
			newSoundID = 0;
		else
			newSoundID = ((m_Sounds.end()--)->first) + 1;

		if (m_Sounds.empty())
			m_Sounds.insert(std::make_pair(newSoundID, Mix_LoadWAV(filePath.c_str())));
		else
			m_Sounds.insert(std::make_pair(newSoundID, Mix_LoadWAV(filePath.c_str())));

		return newSoundID;
	}

	AudioSystem::MusicID SDLAudioSystem::AddMusic(const std::string& filePath)
	{
		MusicID newMusicID{};

		if (m_Music.empty())
			newMusicID = 0;
		else
			newMusicID = ((m_Music.end()--)->first) + 1;

		if (m_Music.empty())
			m_Music.insert(std::make_pair(newMusicID, Mix_LoadMUS(filePath.c_str())));
		else
			m_Music.insert(std::make_pair(newMusicID, Mix_LoadMUS(filePath.c_str())));

		return newMusicID;
	}

	void SDLAudioSystem::Update()
	{
		const float dt{ Timer::GetInstance()->GetElapsedSeconds() };

		for (Channel& channel : m_Channels)
		{
			if (channel.isInUse)
			{
				channel.timeInUse += dt;
				if (channel.timeInUse >= channel.expectedTimeInUse && Mix_Playing(channel.channelIndex) == 0)
				{
					// if both SDL_Mixer and the calculations agree that the sound is no longer playing, set the channel to be used again
					channel.isInUse = false;
					channel.expectedTimeInUse = 0;
					channel.timeInUse = 0;
					channel.soundIDOfChunk = std::numeric_limits<int>::max();
				}
			}
		}
	}

	void SDLAudioSystem::PlaySound(const SoundID soundID, const bool infiniteLoop, const int amountOfLoops, const int volume)
	{
		if (m_Sounds.find(soundID) != m_Sounds.cend())
		{
			int loops{ amountOfLoops };
			if (infiniteLoop)
				loops = -1;

			Mix_VolumeChunk(m_Sounds[soundID], RemapVolumeToSDL(volume));
			Channel& channel{ GetFirstAvailableChannel(m_Channels) };
			if (Mix_PlayChannel(channel.channelIndex, m_Sounds[soundID], loops) == -1)
			{
				// something went wrong
				Logger::LogError((("SDLAudioSystem::PlaySound() > Sound with sound ID: " + std::to_string(soundID)) + " could not be played: ") + Mix_GetError() + "\n");
			}
			else
			{
				channel.isInUse = true;
				channel.expectedTimeInUse = GetChunkTimeInSeconds(m_Sounds[soundID]);
				channel.soundIDOfChunk = soundID;
			}
		}
	}

	void SDLAudioSystem::PlayMusic(const MusicID musicID, const bool infiniteLoop, const int amountOfLoops, const int volume)
	{
		if (m_Music.find(musicID) != m_Music.cend())
		{
			int loops{ amountOfLoops + 1 };
			if (infiniteLoop)
				loops = -1;

			// Mix_PlayingMusic() returns 1 if music is playing, but does not check if a CHANNEL has been paused
			if (m_pCurrentPlayingMusic && Mix_PlayingMusic() == 1)
			{
				// if music is playing, stop the music
				Mix_HaltMusic();
			}

			Mix_VolumeMusic(volume);
			if (Mix_PlayMusic(m_Music[musicID], loops) == -1)
				Logger::LogError((("SDLAudioSystem::PlayMusic() > Music with Music ID: " + std::to_string(musicID)) + " could not be played: ") + Mix_GetError() + "\n");
			else
				m_pCurrentPlayingMusic = m_Music[musicID];
		}
	}

	void SDLAudioSystem::PauseMusic()
	{
		Mix_PauseMusic();
	}

	void SDLAudioSystem::PauseSound(const SoundID soundID)
	{
		for (const Channel& channel : m_Channels)
			if (channel.soundIDOfChunk == soundID)
				return Mix_Pause(channel.channelIndex);
	}

	void SDLAudioSystem::RewindMusic()
	{
		Mix_RewindMusic();
	}

	void SDLAudioSystem::SetMusicPosition(double time)
	{
		switch (Mix_GetMusicType(const_cast<const Mix_Music*>(m_pCurrentPlayingMusic)))
		{
		case MUS_OGG:
		case MUS_MOD:
			if (Mix_SetMusicPosition(time) == -1)
				Logger::LogError(std::string{ "SDLAudioSystem::SetMusicPosition() > SetMusicPosition() failed: " } + Mix_GetError() + "\n");
			break;
		case MUS_MP3:
			RewindMusic();
			if (Mix_SetMusicPosition(time) == -1)
				Logger::LogError(std::string{ "SDLAudioSystem::SetMusicPosition() > SetMusicPosition() failed: " } + Mix_GetError() + "\n");
			break;
		default:
			Logger::LogWarning("SDLAudioSystem::SetMusicPosition() > SetMusicPosition() only supports .mp3, .ogg and .mod music formats\n");
			break;
		}
	}

	void SDLAudioSystem::SetSoundVolume(const SoundID soundID, const int volume)
	{
		if (m_Sounds.find(soundID) != m_Sounds.cend())
			Mix_VolumeChunk(m_Sounds[soundID], RemapVolumeToSDL(volume));
	}

	void SDLAudioSystem::SetMusicVolume(const int volume)
	{
		Mix_VolumeMusic(RemapVolumeToSDL(volume));
	}

	bool SDLAudioSystem::IsMusicPlaying() const
	{
		return Mix_PlayingMusic() == 1;
	}

	bool SDLAudioSystem::IsSoundPlaying(const SoundID soundID) const
	{
		for (const Channel& channel : m_Channels)
			if (channel.soundIDOfChunk == soundID)
				return Mix_Playing(channel.channelIndex) == 1;

		return false;
	}

	int SDLAudioSystem::GetSoundVolume(const SoundID soundID) const
	{
		if (m_Sounds.find(soundID) != m_Sounds.cend())
			return RemapVolumeToIntegrian(Mix_VolumeChunk(m_Sounds.find(soundID)->second, -1));
		else
			return 0;
	}

	int SDLAudioSystem::GetMusicVolume() const
	{
		return RemapVolumeToIntegrian(Mix_VolumeMusic(-1));
	}

	SDLAudioSystem::Channel& SDLAudioSystem::GetFirstAvailableChannel(std::vector<Channel>& channels)
	{
		return (*std::find_if(channels.begin(), channels.end(), [](Channel& c)->bool
			{
				return !c.isInUse;
			}));
	}

	float SDLAudioSystem::GetChunkTimeInSeconds(Mix_Chunk* pChunk) const
	{
		Uint32 points = 0;
		Uint32 frames = 0;
		int freq = 0;
		Uint16 fmt = 0;
		int chans = 0;
		/* Chunks are converted to audio device format */
		if (Mix_QuerySpec(&freq, &fmt, &chans) == 0)
		{
			Logger::LogError(std::string{ "GetChunkTimeInSeconds() failed: " } + SDL_GetError());
			return 0;
		}

		/* bytes / samplesize == sample points */
		points = (pChunk->alen / ((fmt & 0xFF) / 8));

		/* sample points / channels == sample frames */
		frames = (points / chans);

		/* (sample frames * 1000) / frequency == play length in ms */
		return float(frames) / float(freq);
	}

	int SDLAudioSystem::RemapVolumeToSDL(const int volumeInPercentage) const
	{
		return ((volumeInPercentage * m_SDLMixerMaxVolume) / 100);

		// NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
		// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
	}

	int SDLAudioSystem::RemapVolumeToIntegrian(const int volumeInSDL) const
	{
		return ((volumeInSDL * 100) / m_SDLMixerMaxVolume);
	}
}