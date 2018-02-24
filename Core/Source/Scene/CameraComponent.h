#pragma once
#include "Math/Matrix4.h"
#include "Component.h"
#include "Math/Matrix3x4.h"
#include "TransformComponent.h"

namespace Forge
{

	class CameraComponent : public Component
	{
	private:
		TransformComponent* transform;

	public:
		CameraComponent();
		~CameraComponent();

		void Update() override;
		Matrix4 ViewMatrix();
	};

}
