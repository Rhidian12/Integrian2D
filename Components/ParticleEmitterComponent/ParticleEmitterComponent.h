#pragma once

#include "../../Integrian2D_API.h"
#include "../Component/Component.h"
#include "ParticleEmitterSettings.h"

#include <vector>

namespace Integrian2D
{
	class Texture;
	class Particle;

	class ParticleEmitterComponent final : public Component
	{
	public:
		INTEGRIAN2D_API ParticleEmitterComponent(GameObject* const pOwner, Texture* const pTexture, const ParticleEmitterSettings& settings);
		INTEGRIAN2D_API virtual ~ParticleEmitterComponent();

		INTEGRIAN2D_API ParticleEmitterComponent(const ParticleEmitterComponent& other) noexcept;
		INTEGRIAN2D_API ParticleEmitterComponent(ParticleEmitterComponent&& other) noexcept;
		INTEGRIAN2D_API ParticleEmitterComponent& operator=(const ParticleEmitterComponent& other) noexcept;
		INTEGRIAN2D_API ParticleEmitterComponent& operator=(ParticleEmitterComponent&& other) noexcept;

		INTEGRIAN2D_API virtual Component* Clone(GameObject* pOwner) noexcept override;

		INTEGRIAN2D_API virtual void Update() override;
		INTEGRIAN2D_API virtual void Render() const override;

	private:
		ParticleEmitterSettings m_ParticleEmitterSettings;
		std::vector<Particle*> m_Particles;
		Texture* m_pTexture;
		float m_ParticleSpawnerTimer;
	};
}