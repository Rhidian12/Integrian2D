#include "AudioLocator.h"
#include "../Utils/Utils.h"

#include <typeinfo>

namespace Integrian2D
{
	AudioLocator* const AudioLocator::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new AudioLocator{};

		return m_pInstance;
	}

	void AudioLocator::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	AudioLocator::~AudioLocator()
	{
		if (typeid(*m_pAudioSystem) != typeid(NullAudioSystem))
			Utils::SafeDelete(m_pAudioSystem);

		Utils::SafeDelete(m_pNullAudioSystem);
	}

	void AudioLocator::Provide(AudioSystem* const pAudioSystem) noexcept
	{
		m_pAudioSystem = pAudioSystem;
	}

	AudioSystem* const AudioLocator::GetAudio() const noexcept
	{
		return m_pAudioSystem;
	}
}