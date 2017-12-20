#pragma once
#include "Material.h"
#include "Mesh.h"
#include "Math/Matrix3x4.h"

namespace Forge
{

	struct DrawBatch
	{
		Mesh* mesh;
		Material* material;

		const Matrix3x4* worldTransform;
	};

	class Drawable
	{
	protected:
		std::vector<DrawBatch*> _batches;
		bool active;
	public:
		Drawable();
		~Drawable();

		virtual void OnActivate();
		virtual void OnDeactivate();
		virtual void SetActive(bool state);
		bool IsActive() const { return active; }
	};

}
