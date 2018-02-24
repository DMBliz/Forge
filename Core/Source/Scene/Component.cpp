#include "Component.h"

namespace Forge
{

	uint Component::gComponentID;
	void Component::SetActive(bool state)
	{
		if (active == state)
			return;

		if(state)
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}

		active = state;
	}
}
