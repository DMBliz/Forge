#pragma once
#include "Math/Matrix4.h"
#include "Math/Vector2i.h"

namespace Forge
{
	enum class FrustumProjection
	{
		Perspective,
		Orthographic
	};

	class Frustum
	{
	private:
		FrustumProjection projectionType;
		mutable Matrix4 projection;
		Vector2i size;
		float nearf;
		float farf;
		float fov;

	public:
		Frustum();
		Frustum(Frustum& rhs);
		Frustum(const Vector2i& size, float near, float far, FrustumProjection projectionType = FrustumProjection::Perspective);
		
		void SetSize(const Vector2i& newSize);
		void SetNear(float near);
		void SetFar(float far);
		void SetFOV(float fov);

		void SetProjectionType(FrustumProjection newProjection);

		void CalculateMatrix() const ;

		const Matrix4& GetMatrix() const { CalculateMatrix(); return projection; }
	};
}
