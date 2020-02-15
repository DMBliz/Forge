//
// Created by Дмитрий Метелица on 2019-10-24.
//

#pragma once

#include <map>
#include "Platform/Api/Input.h"
#include "FileSystem.h"
#include "WindowSystem.h"
#include "Api.h"

namespace Forge
{
    class PlatformApiProvider
    {
    private:
        std::map<const String, Api*> apis;

    public:
        template<typename T>
        T* getApi(const String& name);

        inline void addApi(const String& name, Api* api)
        {
            apis[name] = api;
        }

        virtual void init();
    };

    template<typename T>
    T* PlatformApiProvider::getApi(const String& name)
    {
        return (T*)apis[name];
    }
}