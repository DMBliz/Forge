#pragma once
#include "Math/Quaternion.h"
#include "Scene/Component.h"
#include "Math/Matrix3x4.h"

namespace Forge
{

	class TransformComponent : public Component
	{
	private:
		Quaternion rotation;
		Vector3 position;
		Vector3 scale;

		TransformComponent* _parent = nullptr;

		mutable Matrix3x4 worldTransform;
		mutable Quaternion worldRotation;

		void UpdateWorldTransform() const;
	public:
		TransformComponent();
		~TransformComponent();

		const Vector3& Position() const;
		const Quaternion& Rotation() const;
		const Vector3& Scale() const;

		Vector3 GetWorldScale() const;
		Vector3 GetWorldPosition() const;
		Quaternion GetWorldRotation() const;

		void Position(const Vector3& vector);
		void Rotation(const Quaternion& quaternion);
		void Scale(const Vector3& vector);

		void SetParent(TransformComponent* parent);
		Matrix3x4 GetTransform() const;
		Quaternion GetRotation() const;
		const Matrix3x4* GetWorldTransform() const;
	};

}

#include "Serialization/Meta.h"

namespace meta
{
	template<>
	inline auto registerMembers<Forge::TransformComponent>()
	{
		return members(
			member("position", &Forge::TransformComponent::Position, &Forge::TransformComponent::Position),
			member("rotation", &Forge::TransformComponent::Rotation, &Forge::TransformComponent::Rotation),
			member("scale", &Forge::TransformComponent::Scale, &Forge::TransformComponent::Scale)
		);
	}
	
}
