#include "ParticleEmitterComponent.h"
#include "Particle.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../Utils/Utils.h"
#include "../../Timer/Timer.h"

#include <algorithm>

namespace Integrian2D
{
	ParticleEmitterComponent::ParticleEmitterComponent(GameObject* const pOwner, Texture* const pTexture, const ParticleEmitterSettings& settings)
		: Component{ pOwner }
		, m_ParticleEmitterSettings{ settings }
		, m_Particles{}
		, m_pTexture{ pTexture }
		, m_ParticleSpawnerTimer{}
	{
		m_Particles.reserve(settings.maximumNumberOfParticles);

		for (int i{}; i < settings.maximumNumberOfParticles; ++i)
			m_Particles.push_back(new Particle{});
	}

	ParticleEmitterComponent::~ParticleEmitterComponent()
	{
		for (Particle*& pParticle : m_Particles)
			Utils::SafeDelete(pParticle);
	}

#pragma region Rule Of 5
	ParticleEmitterComponent::ParticleEmitterComponent(const ParticleEmitterComponent& other) noexcept
		: Component{ m_pOwner }
		, m_ParticleEmitterSettings{ other.m_ParticleEmitterSettings }
		, m_Particles{}
		, m_pTexture{ other.m_pTexture }
		, m_ParticleSpawnerTimer{ other.m_ParticleSpawnerTimer }
	{
		m_Particles.reserve(m_ParticleEmitterSettings.maximumNumberOfParticles);

		for (int i{}; i < m_ParticleEmitterSettings.maximumNumberOfParticles; ++i)
		{
			m_Particles.push_back(new Particle{ *other.m_Particles[i] });
			m_Particles.back()->Initialize(m_pOwner->pTransform->GetWorldPosition(), m_pTexture, m_ParticleEmitterSettings);
		}
	}

	ParticleEmitterComponent::ParticleEmitterComponent(ParticleEmitterComponent&& other) noexcept
		: Component{ std::move(m_pOwner) }
		, m_ParticleEmitterSettings{ std::move(other.m_ParticleEmitterSettings) }
		, m_Particles{ std::move(other.m_Particles) }
		, m_pTexture{ std::move(other.m_pTexture) }
		, m_ParticleSpawnerTimer{ std::move(other.m_ParticleSpawnerTimer) }
	{
		other.m_Particles.clear();
	}

	ParticleEmitterComponent& ParticleEmitterComponent::operator=(const ParticleEmitterComponent& other) noexcept
	{
		m_pOwner = other.m_pOwner;
		m_ParticleEmitterSettings = other.m_ParticleEmitterSettings;
		m_pTexture = other.m_pTexture;
		m_ParticleSpawnerTimer = other.m_ParticleSpawnerTimer;

		m_Particles.reserve(m_ParticleEmitterSettings.maximumNumberOfParticles);

		for (int i{}; i < m_ParticleEmitterSettings.maximumNumberOfParticles; ++i)
		{
			m_Particles.push_back(new Particle{ *other.m_Particles[i] });
			m_Particles.back()->Initialize(m_pOwner->pTransform->GetWorldPosition(), m_pTexture, m_ParticleEmitterSettings);
		}

		return *this;
	}

	ParticleEmitterComponent& ParticleEmitterComponent::operator=(ParticleEmitterComponent&& other) noexcept
	{
		m_pOwner = std::move(other.m_pOwner);
		m_ParticleEmitterSettings = std::move(other.m_ParticleEmitterSettings);
		m_pTexture = std::move(other.m_pTexture);
		m_Particles = std::move(other.m_Particles);
		m_ParticleSpawnerTimer = std::move(other.m_ParticleSpawnerTimer);

		return *this;
	}
#pragma endregion

	Component* ParticleEmitterComponent::Clone(GameObject* pOwner) noexcept
	{
		return new ParticleEmitterComponent{ pOwner, m_pTexture, m_ParticleEmitterSettings };
	}

	void ParticleEmitterComponent::Update()
	{
		m_ParticleSpawnerTimer += Timer::GetInstance()->GetElapsedSeconds();

		if (m_ParticleSpawnerTimer >= m_ParticleEmitterSettings.spawnInterval)
		{
			auto cIt{ std::find_if(m_Particles.cbegin(), m_Particles.cend(), [](const Particle* const pParticle)->bool
				{
					return pParticle->GetIsActive();
				}) };

			if (cIt != m_Particles.cend())
				(*cIt)->Initialize(m_pOwner->pTransform->GetWorldPosition(), m_pTexture, m_ParticleEmitterSettings);

			m_ParticleSpawnerTimer = 0.f;
		}

		for (Particle* const pParticle : m_Particles)
			pParticle->Update();
	}

	void ParticleEmitterComponent::Render() const
	{
		for (const Particle* const pParticle : m_Particles)
			pParticle->Render();
	}
}