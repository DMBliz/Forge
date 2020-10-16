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
    
    float cameraSpeedModificator = 1.0f;
	float cameraMovementSpeed = 2.5f;
	float cameraMouseSensitivity = 0.2f;
	float cameraZoom = 45.0f;



	inline Forge::Matrix4 GetViewMatrix()
	{
		Forge::Matrix4 ret = Forge::Matrix4::Identity;

		Forge::Vector3 eye = cameraPosition;
		Forge::Vector3 target = eye + cameraFront;

		Forge::Vector3 zaxis = (eye - target).Normalized();
		Forge::Vector3 xaxis = cameraUp.Cross(zaxis).Normalized();
		Forge::Vector3 yaxis = xaxis.Cross(zaxis).Normalized();

		ret.mels[0][0] = xaxis.x;
		ret.mels[0][1] = xaxis.y;
		ret.mels[0][2] = xaxis.z;
		ret.mels[1][0] = yaxis.x;
		ret.mels[1][1] = yaxis.y;
		ret.mels[1][2] = yaxis.z;
		ret.mels[2][0] = zaxis.x;
		ret.mels[2][1] = zaxis.y;
		ret.mels[2][2] = zaxis.z;

		ret.mels[0][3] = -xaxis.Dot(eye);
		ret.mels[1][3] = -yaxis.Dot(eye);
		ret.mels[2][3] = -zaxis.Dot(eye);

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
        bool changed = false;
        if(Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::LeftShift) == Forge::InputState::Hold)
        {
            cameraSpeedModificator = 2.0f;
        }
	    else  if(Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::LeftShift) == Forge::InputState::None)
        {
            cameraSpeedModificator = 1.0f;
        }


		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::W) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition += cameraFront * velocity * cameraSpeedModificator;
            changed = true;
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::S) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition -= cameraFront * velocity * cameraSpeedModificator;
            changed = true;
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::A) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition -= cameraRight * velocity * cameraSpeedModificator;
            changed = true;
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::D) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition += cameraRight * velocity * cameraSpeedModificator;
            changed = true;
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::Q) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition -= cameraUp * velocity * cameraSpeedModificator;
            changed = true;
		}
		if (Forge::engine->GetInputSystem()->GetKeyState(Forge::KeyboardKey::E) == Forge::InputState::Hold)
		{
			float velocity = cameraMovementSpeed * Forge::Timer::DeltaTime();
			cameraPosition += cameraUp * velocity * cameraSpeedModificator;
            changed = true;
		}
		if (Forge::engine->GetInputSystem()->GetCursorDelta() != Forge::Vector2::Zero && Forge::engine->GetInputSystem()->GetMouseButtonState(Forge::MouseButton::Right) == Forge::InputState::Hold)
		{
			cameraRotation.x += Forge::engine->GetInputSystem()->GetCursorDelta().x * cameraMouseSensitivity;
			cameraRotation.y -= Forge::engine->GetInputSystem()->GetCursorDelta().y * cameraMouseSensitivity;

			if(cameraRotation.y > 89.0f)
			{
				cameraRotation.y = 89.0f;
			}else if(cameraRotation.y < -89.0f)
			{
				cameraRotation.y = -89.0f;
			}

            changed = true;
		}

        if(changed)
            UpdateVectors();

	}
}
