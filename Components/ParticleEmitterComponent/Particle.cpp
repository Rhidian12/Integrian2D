#include "Particle.h"
#include "../../Timer/Timer.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	void Particle::Update() noexcept
	{
		if (!m_IsActive)
			return;

		const float dt{ Timer::GetInstance()->GetElapsedSeconds() };

		/* Subtract lifetime */
		m_CurrentTime -= dt;

		/* If the lifetime is lower than 0, deactivate the particle */
		if (m_CurrentTime <= 0.f)
		{
			m_IsActive = false;
			return;
		}

		/* Update position */
		m_Position += Point2f{ m_Velocity * dt * m_Speed };

		/* Cache how long the particle is in its lifetime */
		const float particleRemainingLifetime{ m_CurrentTime / m_MaximumTime };

		/* Update colour */
		m_Colour.a = Betteruint8_t{ static_cast<uint8_t>(particleRemainingLifetime* 2.f) };

		/* Update size */
		if (m_SizeGrow >= 0)
			m_CurrentSize = m_InitialSize + (m_InitialSize * (m_SizeGrow * particleRemainingLifetime));
		else
			m_CurrentSize = m_InitialSize - (m_InitialSize * (m_SizeGrow * particleRemainingLifetime));
	}

	void Particle::Render() const noexcept
	{
		if (!m_IsActive)
			return;

		if (m_pTexture)
			Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ m_Position, m_CurrentSize, m_CurrentSize }, Rectf{});
		else
			Renderer::GetInstance()->RenderFilledPolygon(
				{
					m_Position,
					Point2f{ m_Position.x, m_Position.y + m_CurrentSize },
					Point2f{ m_Position.x + m_CurrentSize, m_Position.y + m_CurrentSize },
					Point2f{ m_Position.x + m_CurrentSize, m_Position.y }
				},
				m_Colour);
	}

	bool Particle::GetIsActive() const noexcept
	{
		return m_IsActive;
	}
}