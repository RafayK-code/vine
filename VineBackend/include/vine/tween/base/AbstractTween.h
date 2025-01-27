#pragma once

namespace vine
{
    class AbstractTween
    {
    public:
        AbstractTween();
        virtual ~AbstractTween() = default;

        int iterations;

    protected:
        virtual void onStart();
        virtual void onComplete();

        bool didStart_;
        bool didComplete_;
    };
}