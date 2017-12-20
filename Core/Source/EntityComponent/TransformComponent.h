#pragma once
#include "Math/Quaternion.h"
#include "Component.h"
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

		Vector3 Position() const;
		Quaternion Rotation() const;
		Vector3 Scale() const;

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
