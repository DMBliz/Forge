#pragma once

namespace Forge
{
 
    class ISwitchable
    {
    private:
        bool active;
    public:
        virtual void OnEnable() = 0;
        virtual void OnDisable() = 0;

        bool IsActive() const;
        void SetActive(bool state);
    };

}