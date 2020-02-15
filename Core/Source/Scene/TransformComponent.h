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

		Vector3 Up() const { return rotation * Vector3::Up; }
		Vector3 Right() const { return rotation * Vector3::Right; }
		Vector3 Forward() const { return rotation * Vector3::Forward; }

		void Parent(TransformComponent* parent);
		TransformComponent* Parent() const;

		Matrix3x4 GetTransform() const;
		Quaternion GetRotation() const;
		const Matrix3x4* GetWorldTransform() const;
	};

}
