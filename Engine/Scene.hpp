#pragma once

namespace Engine
{
    class Scene
    {
        bool _started = false;

    public:
        void start()
        {
            if (!_started)
            {
                this->init();
                _started = true;
            }
            else
            {
                this->resume();
            }
        }

        void reset()
        {
            _started = false;
        }

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void handleInput() = 0;

        void pause() {}
        void resume() {}
    };

}
