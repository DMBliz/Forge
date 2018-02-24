#pragma once
#include "Math/Matrix4.h"

namespace Forge
{

	class Camera
	{
		Matrix4 view;
	public:
		Camera();
		~Camera();

		const Matrix4& GetViewMatrix() const 
		{
			return view;
		}

		void SetMatrix(const Matrix4& matrix)
		{
			view = matrix;
			view.mels[0][3] = -view.mels[0][3];
			view.mels[1][3] = -view.mels[1][3];
			view.mels[2][3] = -view.mels[2][3];
		}
	};

}
