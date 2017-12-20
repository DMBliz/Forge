#include "TransformComponent.h"
#include "Math/Matrix3x4.h"

namespace Forge
{
	void TransformComponent::UpdateWorldTransform() const
	{
		if(_parent != nullptr)
		{
			_parent->UpdateWorldTransform();
			worldTransform = _parent->worldTransform * GetTransform();
			worldRotation = _parent->worldRotation * GetRotation();
		}else
		{
			worldTransform = GetTransform();
			worldRotation = GetRotation();
		}
	}

	TransformComponent::TransformComponent()
	{}

	TransformComponent::~TransformComponent()
	{}

	Vector3 TransformComponent::Position() const
	{
		return position;
	}

	Quaternion TransformComponent::Rotation() const
	{
		return rotation;
	}

	Vector3 TransformComponent::Scale() const
	{
		return scale;
	}

	Vector3 TransformComponent::GetWorldScale() const
	{
		UpdateWorldTransform();
		return worldTransform.Scale();
	}

	Vector3 TransformComponent::GetWorldPosition() const
	{
		UpdateWorldTransform();
		return worldTransform.Translation();
	}

	Quaternion TransformComponent::GetWorldRotation() const
	{
		UpdateWorldTransform();
		return worldRotation;
	}

	void TransformComponent::Position(const Vector3& vector)
	{
		position = vector;
	}

	void TransformComponent::Rotation(const Quaternion& quaternion)
	{
		rotation = quaternion;
	}

	void TransformComponent::Scale(const Vector3& vector)
	{
		scale = vector;
	}

	void TransformComponent::SetParent(TransformComponent* parent)
	{
		_parent = parent;
	}

	Matrix3x4 TransformComponent::GetTransform() const
	{
		return Matrix3x4(position, rotation, scale);
	}

	Quaternion TransformComponent::GetRotation() const
	{
		return rotation;
	}

	const Matrix3x4* TransformComponent::GetWorldTransform() const
	{
		return &worldTransform;
	}
}
