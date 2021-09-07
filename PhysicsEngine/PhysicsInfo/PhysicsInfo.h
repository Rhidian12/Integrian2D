#pragma once

#include "../../Utils/Utils.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class IPhysicsInfo
	{
	public:
		virtual ~IPhysicsInfo() = default;
	};

	template<typename Type>
	class PhysicsInfoImpl final : public IPhysicsInfo
	{
	public:
		PhysicsInfoImpl(const Type data)
			: m_Data{ data }
		{}

		const Type& GetData() const noexcept
		{
			return m_Data;
		}

	private:
		Type m_Data;
	};

	struct PhysicsInfo final
	{
	public:
		template<int P, typename Type>
		PhysicsInfo(const float _mass, const Vector2f _velocity, const Polygon<P, Type> hitbox)
			: mass{ _mass }
			, velocity{ _velocity }
			, pHitbox{ new PhysicsInfoImpl{hitbox} }
		{}

		~PhysicsInfo();

#pragma region Rule Of 5
		PhysicsInfo(const PhysicsInfo& other) noexcept;
		PhysicsInfo(PhysicsInfo&& other) noexcept;
		PhysicsInfo& operator=(const PhysicsInfo& other) noexcept;
		PhysicsInfo& operator=(PhysicsInfo&& other) noexcept;
#pragma endregion

		template<int P, typename Type>
		Polygon<P, Type> GetHitbox() const noexcept
		{
			static_cast<PhysicsInfoImpl*>(pHitbox)->GetData();
		}

		float mass;
		Vector2f velocity;
		IPhysicsInfo* pHitbox;
	};
}