#include "Engine.hpp"

namespace Engine
{
    Engine::Engine(sf::RenderWindow &window) : window(&window) {}

    void Engine::run()
    {
        start();

        while (this->window->isOpen())
        {
            deltaTime = _clock.restart().asSeconds();

            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    this->close();

                sceneManager.getActive()->handleInput();
            }

            if (sceneManager.activeSceneName != "")
            {
                sceneManager.getActive()->update();
                sceneManager.getActive()->render();
            }

            update();
            window->display();
        }
    }

    void Engine::close()
    {
        window->close();
    }
}
