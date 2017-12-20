#pragma once
#include "Drawable.h"

namespace Forge
{

	class Model : public Drawable
	{
	
	public:
		Model();
		~Model();
		void EnableDrawing();
		void DisableDrawing();
	};

}
