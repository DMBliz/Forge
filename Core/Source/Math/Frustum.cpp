#include "Frustum.h"
#include "Math/Mathf.h"

namespace Forge
{
	void Frustum::CalculateMatrix() const
	{
		switch (projectionType)
		{
			case FrustumProjection::Orthographic: 
				projection = Matrix4::Orthographic(0, size.x, 0, size.y, nearf, farf);
				break;
			case FrustumProjection::Perspective: 
				projection = Matrix4::Perspective(fov, static_cast<float>(size.x) / static_cast<float>(size.y), nearf, farf);
				break;
		}
	}

	Frustum::Frustum()
		: projectionType(FrustumProjection::Perspective), nearf(0.1f), farf(100), fov(45.0f), size(800, 600)
	{
		CalculateMatrix();
	}

	Frustum::Frustum(Frustum& rhs)
		: projectionType(rhs.projectionType), projection(rhs.projection), nearf(rhs.nearf), farf(rhs.farf), fov(rhs.fov)
	{}

	Frustum::Frustum(const Vector2i& size, float near, float far, FrustumProjection projectionType)
		:projectionType(projectionType), size(size), nearf(near), farf(far)
	{
		CalculateMatrix();
	}

	void Frustum::SetSize(const Vector2i& newSize)
	{
		size = newSize;
	}

	void Frustum::SetNear(float near)
	{
		this->nearf = near;
	}

	void Frustum::SetFar(float far)
	{
		this->farf = far;
	}

	void Frustum::SetFOV(float fov)
	{
		this->fov = fov;
	}

	void Frustum::SetProjectionType(FrustumProjection newProjection)
	{
		projectionType = newProjection;
	}
}
