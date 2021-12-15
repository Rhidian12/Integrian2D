#pragma once

#include "../AudioSystem/AudioSystem.h"

#include <vector>
#include <map>

struct Mix_Chunk;
struct _Mix_Music;

namespace Integrian2D
{
	class SDLAudioSystem final : public AudioSystem
	{
	public:
		SDLAudioSystem();
		virtual ~SDLAudioSystem();

		virtual SoundID AddSound(const std::string& filePath) override;
		virtual MusicID AddMusic(const std::string& filePath) override;

		virtual void Update() override;

		virtual void PlaySound(const SoundID soundID, const bool infiniteLoop = false, const int amountOfLoops = 0, const int volume = 100) override;
		virtual void PlayMusic(const MusicID musicID, const bool infiniteLoop = false, const int amountOfLoops = 0, const int volume = 100) override;

		virtual void PauseMusic() override;
		virtual void PauseSound(const SoundID soundID) override;

		virtual void RewindMusic() override;
		virtual void SetMusicPosition(double time) override;

		virtual void SetSoundVolume(const SoundID soundID, const int volume) override;
		virtual void SetMusicVolume(const int volume) override;

		virtual bool IsMusicPlaying() const override;
		virtual bool IsSoundPlaying(const SoundID soundID) const override;

		virtual int GetSoundVolume(const SoundID soundID) const override;
		virtual int GetMusicVolume() const override;

	private:
		struct Channel final
		{
			Channel(const uint16_t index)
				: channelIndex{ index }
			{}

			bool isInUse{ false };
			uint16_t channelIndex; // uint16_t because the range is [0 - 7]
			float timeInUse{};
			float expectedTimeInUse{};
			SoundID soundIDOfChunk{ std::numeric_limits<int>::max() }; // use max to minimize the possibility of it taking an existing ID
		};

		Channel& GetFirstAvailableChannel(std::vector<Channel>& channels);
		float GetChunkTimeInSeconds(Mix_Chunk* pChunk) const; // reference: https://discourse.libsdl.org/t/time-length-of-sdl-mixer-chunks/12852
		int RemapVolumeToSDL(const int volumeInPercentage) const;
		int RemapVolumeToIntegrian(const int volumeInSDL) const;

		std::map<SoundID, Mix_Chunk*> m_Sounds;
		std::map<MusicID, _Mix_Music*> m_Music;

		std::vector<Channel> m_Channels;

		_Mix_Music* m_pCurrentPlayingMusic;

		const int m_SDLMixerMaxVolume; /* SDL_Mixer */

		using SoundPair = std::pair<SoundID, Mix_Chunk*>;
		using MusicPair = std::pair<MusicID, _Mix_Music*>;
	};
}