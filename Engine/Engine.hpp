#pragma once

#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace Engine
{
    class Engine
    {
    public:
        SceneManager sceneManager;
        sf::RenderWindow *window;
        AssetManager assetManager;
        InputManager inputManager;
        float deltaTime;
        sf::Event event;

        Engine(sf::RenderWindow &window);

        void run();
        void close();

        virtual void start() = 0;
        virtual void update() = 0;

    private:
        sf::Clock _clock;
    };

}
