#include "ISwitchable.h"

namespace Forge
{

    bool ISwitchable::IsActive() const
    {
        return active;
    }

    void ISwitchable::SetActive(bool state)
    {
        if (state == active)
            return;

        if (state == true)
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
