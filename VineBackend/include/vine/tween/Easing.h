#pragma once

namespace vine
{
    namespace easing
    {
        using EasingFunction = float(*)(float, float, float, float);

        class Linear
        {
        public:
            static float easeNone(float currTime, float initial, float delta, float totalTime);
        };

        class Sinusoidal
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Quadratic
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Cubic
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Quartic
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Quintic
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Exponential
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Circular
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Back
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Elastic
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };

        class Bounce
        {
        public:
            static float easeIn(float currTime, float initial, float delta, float totalTime);
            static float easeOut(float currTime, float initial, float delta, float totalTime);
            static float easeInOut(float currTime, float initial, float delta, float totalTime);
        };
    }
}