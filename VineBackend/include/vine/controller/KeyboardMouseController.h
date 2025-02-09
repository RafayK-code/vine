#pragma once

#include <vine/controller/Controller.h>
#include <vine/core/codes/KeyCodes.h>
#include <vine/core/codes/MouseCodes.h>

#include <vine/util/Math.h>

#include <bitset>

namespace vine
{
    class KeyboardMouseController : public Controller
    {
    public:
        KeyboardMouseController();
        ~KeyboardMouseController();

        virtual void dispatchSDLEvents(const SDL_Event* event) override;
        virtual Type getType() const override { return Type::Keyboard; }

        Vec2 getMousePos() const;

        bool isKeyDown(KeyCode key) const;
        bool isMouseButtonDown(MouseCode button) const;

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