#include "SceneManager.hpp"

namespace Engine
{
    void SceneManager::registerScene(std::string name, Scene *scene)
    {
        _scenes[name] = scene;
    }

    void SceneManager::setActive(std::string name)
    {
        if (activeSceneName != "")
            getActive()->pause();

        activeSceneName = name;
        getActive()->start();
    }

    Scene *SceneManager::getActive()
    {
        return _scenes.at(activeSceneName);
    }

}
