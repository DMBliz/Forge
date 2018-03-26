#pragma once
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

namespace Forge
{

	class Camera
	{
		Matrix4 _view;
        Vector3 _position;
	public:
		Camera();
		~Camera();

        const Matrix4& GetViewMatrix() const
        {
            return _view;
        }

        const Vector3& GetPosition() const
        {
            return _position;
        }

        void SetMatrix(const Matrix4& matrix)
        {
            _view = matrix;
        }

        void SetPosition(const Vector3& position)
        {
            _position = position;
        }
	};

}
