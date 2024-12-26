#pragma once

#include <vine/controller/Controller.h>
#include <vine/core/codes/KeyCodes.h>

#include <glm/glm.hpp>

namespace vine
{
    class KeyboardMouseController : public Controller
    {
    public:
        KeyboardMouseController();
        ~KeyboardMouseController();

        virtual void dispatchSDLEvents(const SDL_Event* event) override;
        virtual Type getType() const override { return Type::Keyboard; }

        glm::vec2 getMousePos() const;
        bool isKeyDown(KeyCode key) const;

        enum class State
        {
            Default,
            Typing,
        };

        void setState(State state);
        State getState() const { return state_; }

    private:
        State state_;
    };
}