#pragma once

#include "../../Integrian2D_API.h"
#include "../../Component/Component.h"
#include "ParticleEmitterSettings.h"
#include "Particle.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../Utils/Utils.h"
#include "../../Timer/Timer.h"

#include <vector>
#include <algorithm>

namespace Integrian2D
{
	class Texture;
	class Particle;

	template<EmitterShape Shape>
	class ParticleEmitterComponent final : public Component
	{
	public:
		ParticleEmitterComponent(GameObject* const pOwner, Texture* const pTexture, const ParticleEmitterSettings<Shape>& settings);
		virtual ~ParticleEmitterComponent();

		ParticleEmitterComponent(const ParticleEmitterComponent&) noexcept = delete;
		ParticleEmitterComponent(ParticleEmitterComponent&&) noexcept = delete;
		ParticleEmitterComponent& operator=(const ParticleEmitterComponent&) noexcept = delete;
		ParticleEmitterComponent& operator=(ParticleEmitterComponent&&) noexcept = delete;

		virtual void Update() override;
		virtual void Render() const override;

	private:
		ParticleEmitterSettings<Shape> m_ParticleEmitterSettings;
		std::vector<Particle*> m_Particles;
		Texture* m_pTexture;
		float m_ParticleSpawnerTimer;
	};

#pragma region Function Definitions
	template<EmitterShape Shape>
	ParticleEmitterComponent<Shape>::ParticleEmitterComponent(GameObject* const pOwner, Texture* const pTexture, const ParticleEmitterSettings<Shape>& settings)
		: Component{ pOwner }
		, m_ParticleEmitterSettings{ settings }
		, m_Particles{}
		, m_pTexture{ pTexture }
		, m_ParticleSpawnerTimer{}
	{
		m_Particles.reserve(settings.maximumNumberOfParticles);

		for (int i{}; i < settings.maximumNumberOfParticles; ++i)
			m_Particles.push_back(new Particle{});

		if constexpr (Shape == EmitterShape::Cone)
		{
			const Vector2f& coneDirection{ m_ParticleEmitterSettings.shapeSpecificData.coneDirection };

			const float angle{
				arccos(Dot(coneDirection, m_ParticleEmitterSettings.startingVelocity)  /
				(Magnitude(coneDirection) * Magnitude(m_ParticleEmitterSettings.startingVelocity)))
			};

			ASSERT(Utils::IsInRange(angle,
				m_ParticleEmitterSettings.shapeSpecificData.coneNegativeAngle,
				m_ParticleEmitterSettings.shapeSpecificData.conePositiveAngle),
				"ConeEmitterSettings > The starting velocity is not in the direction of the cone or exceeds the cone angle limits");
		}
	}

	template<EmitterShape Shape>
	ParticleEmitterComponent<Shape>::~ParticleEmitterComponent()
	{
		for (Particle*& pParticle : m_Particles)
			Utils::SafeDelete(pParticle);
	}

	template<EmitterShape Shape>
	void ParticleEmitterComponent<Shape>::Update()
	{
		m_ParticleSpawnerTimer += Timer::GetInstance()->GetElapsedSeconds();

		if (m_ParticleSpawnerTimer >= m_ParticleEmitterSettings.spawnInterval)
		{
			auto cIt{ std::find_if(m_Particles.cbegin(), m_Particles.cend(), [](const Particle* const pParticle)->bool
				{
					return !pParticle->GetIsActive();
				}) };

			if (cIt != m_Particles.cend())
				(*cIt)->Initialize(m_pOwner->pTransform->GetWorldPosition(), m_pTexture, m_ParticleEmitterSettings);

			m_ParticleSpawnerTimer = 0.f;
		}

		for (Particle* const pParticle : m_Particles)
			pParticle->Update();
	}

	template<EmitterShape Shape>
	void ParticleEmitterComponent<Shape>::Render() const
	{
		for (const Particle* const pParticle : m_Particles)
			pParticle->Render();
	}
#pragma endregion

	using ConeParticleEmitterComponent = ParticleEmitterComponent<EmitterShape::Cone>;
	using CircleParticleEmitterComponent = ParticleEmitterComponent<EmitterShape::Circle>;
}