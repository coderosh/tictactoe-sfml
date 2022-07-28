#pragma once

#include <map>
#include <stack>
#include <iostream>
#include "Scene.hpp"

namespace Engine
{
    class SceneManager
    {
    public:
        std::string activeSceneName;

        void registerScene(std::string name, Scene *scene);
        void setActive(std::string name);
        Scene *getActive();

    private:
        std::map<std::string, Scene *> _scenes;
    };
}
