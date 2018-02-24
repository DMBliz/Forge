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
		:scale(Vector3(1.0f, 1.0f, 1.0f))
	{}

	TransformComponent::~TransformComponent()
	{}

	const Vector3& TransformComponent::Position() const
	{
		return position;
	}

	const Quaternion& TransformComponent::Rotation() const
	{
		return rotation;
	}

	const Vector3& TransformComponent::Scale() const
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
		UpdateWorldTransform();
	}

	void TransformComponent::Rotation(const Quaternion& quaternion)
	{
		rotation = quaternion;
		UpdateWorldTransform();
	}

	void TransformComponent::Scale(const Vector3& vector)
	{
		scale = vector;
		UpdateWorldTransform();
	}

	void TransformComponent::Parent(TransformComponent* parent)
	{
		_parent = parent;
		UpdateWorldTransform();
	}

	TransformComponent* TransformComponent::Parent() const
	{
		return _parent;
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
