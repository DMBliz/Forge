#pragma once
#include "Containers/String.h"

namespace Forge
{
	//TODO: end this
	class Font
	{
	private:
		String fontName;
		int fontSize;

	public:
		Font();
		~Font();

		void Resize(int size);
	};

}
