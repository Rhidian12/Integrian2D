#pragma once

#include "../../Math/TypeDefines.h"
#include "ParticleEmitterSettings.h"

namespace Integrian2D
{
	class Texture;

	class Particle final
	{
		Particle(const Point2f& _position, Texture* const pTexture, const ParticleEmitterSettings& settings);

		void Update() noexcept;
		void Render() const noexcept;

	private:
		Point2f m_Position;
		RGBColour m_Colour;
		Texture* m_pTexture;
		Vector2f m_Velocity;

		float m_CurrentSize;
		float m_InitialSize;
		float m_CurrentTime;
		float m_MaximumTime;
		float m_SizeGrow; /* Percentual grow during the particle's lifetime (< 0 == shrink, 0 > == grow) */
		float m_Rotation;
		bool m_IsActive;
	};
}