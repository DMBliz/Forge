#include "CameraComponent.h"
#include "Entity.h"
#include "Graphics/Renderer.h"
#include "Core/Engine.h"

namespace Forge
{
	CameraComponent::CameraComponent()
	{}


	CameraComponent::~CameraComponent()
	{}

	void CameraComponent::Update()
	{
		engine->GetRenderer()->SetViewMatrix(ViewMatrix());
	}

	Matrix4 CameraComponent::ViewMatrix()
	{
		if(transform != nullptr)
		{
			return transform->GetTransform().ToMatrix4();
		}else
		{
			transform = GetOwner()->GetComponent<TransformComponent>();
			if(transform != nullptr)
			{
				return transform->GetTransform().ToMatrix4();
			}
		}
		return Matrix4::Identity;
	}
}
