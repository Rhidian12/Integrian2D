#include "Particle.h"
#include "../../Utils/Utils.h"
#include "../../Timer/Timer.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	Particle::Particle()
		: m_Position{}
		, m_Colour{}
		, m_pTexture{}
		, m_Velocity{}
		, m_CurrentSize{}
		, m_InitialSize{}
		, m_CurrentTime{}
		, m_MaximumTime{}
		, m_SizeGrow{}
		, m_Rotation{}
		, m_IsActive{}
	{}

	void Particle::Initialize(const Point2f& _position, Texture* const pTexture, const ParticleEmitterSettings& settings) noexcept
	{
		/* Set the particle to true */
		m_IsActive = true;

		/* Set position */
		m_Position = _position;

		/* Set texture */
		m_pTexture = pTexture;

		/* Set lifetime */
		m_MaximumTime = Utils::RandomNumber(settings.minimumTime, settings.maximumTime);
		m_CurrentTime = m_MaximumTime;

		/* Set size */
		m_InitialSize = Utils::RandomNumber(settings.minimumSpawnSize, settings.maximumSpawnSize);
		m_CurrentSize = m_InitialSize;

		/* Set size grow */
		m_SizeGrow = Utils::RandomNumber(settings.minimumSizeGrow, settings.maximumSizeGrow);

		/* Set rotation */
		m_Rotation = static_cast<float>(Utils::RandomNumber(-Utils::PI, Utils::PI));

		/* Set velocity */
		const float c{ cosf(m_Rotation) };
		const float s{ sinf(m_Rotation) };

		m_Velocity.x = m_Velocity.x * c - m_Velocity.y * s;
		m_Velocity.y = m_Velocity.x * s + m_Velocity.y * c;
	}

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
		m_Position += Point2f{ m_Velocity * dt };

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
}