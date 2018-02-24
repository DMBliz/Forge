#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Utilities/Timer.h"

namespace ForgeEditor
{
	Forge::Vector3 cameraPosition;
	Forge::Vector3 cameraFront;
	Forge::Vector3 cameraUp;
	Forge::Vector3 cameraRight;
	Forge::Vector2 cameraRotation;

	float cameraMovementSpeed = 2.5f;
	float cameraMouseSensitivity = 0.2f;
	float cameraZoom = 45.0f;



	inline Forge::Matrix4 GetViewMatrix()
	{
		
		Forge::Matrix4 ret = Forge::Matrix4::Identity;

		ret.mels[0][0] = cameraRight.x;
		ret.mels[1][0] = cameraRight.y;
		ret.mels[2][0] = cameraRight.z;
		ret.mels[0][1] = cameraUp.x;
		ret.mels[1][1] = cameraUp.y;
		ret.mels[2][1] = cameraUp.z;
		ret.mels[0][2] = -cameraFront.x;
		ret.mels[1][2] = -cameraFront.y;
		ret.mels[2][2] = -cameraFront.z;
		ret.mels[0][3] = -cameraRight.Dot(cameraPosition);
		ret.mels[1][3] = -cameraUp.Dot(cameraPosition);
		ret.mels[2][3] = -cameraFront.Dot(cameraPosition);

		return ret;
	}

	inline void UpdateVectors()
	{
		cameraFront = Forge::Vector3(cos(cameraRotation.x * Forge::DEGTORAD) * cos(cameraRotation.y * Forge::DEGTORAD), sin(cameraRotation.y * Forge::DEGTORAD), sin(cameraRotation.x * Forge::DEGTORAD) * cos(cameraRotation.y * Forge::DEGTORAD)).Normalized();
		cameraRight = cameraFront.Cross(Forge::Vector3::Up).Normalized();
		cameraUp = cameraRight.Cross(cameraFront).Normalized();
	}

	inline void UpdateCamera()
	{
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::W) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition += cameraFront * velocity;
			UpdateVectors();
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::S) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition -= cameraFront * velocity;
			UpdateVectors();
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::A) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition += cameraRight * velocity;
			UpdateVectors();
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::D) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition -= cameraRight * velocity;
			UpdateVectors();
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::Q) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition -= cameraUp * velocity;
			UpdateVectors();
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::E) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition += cameraUp * velocity;
			UpdateVectors();
		}
		if (Forge::engine->GetInputSystem()->GetCursorDelta() != Forge::Vector2::Zero && Forge::engine->GetInputSystem()->GetMouseButtonState(Forge::MouseButton::Right) == Forge::InputState::Hold)
		{
			cameraRotation.x += Forge::engine->GetInputSystem()->GetCursorDelta().x * cameraMouseSensitivity;
			cameraRotation.y += Forge::engine->GetInputSystem()->GetCursorDelta().y * cameraMouseSensitivity;

			if(cameraRotation.y > 89.0f)
			{
				cameraRotation.y = 89.0f;
			}else if(cameraRotation.y < -89.0f)
			{
				cameraRotation.y = -89.0f;
			}

			UpdateVectors();
		}
	}
}
