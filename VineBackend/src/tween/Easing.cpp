#include <vine/tween/Easing.h>

#include <vine/util/Math.h>

namespace vine
{
    namespace easing
    {
        float Linear::easeNone(float currTime, float initial, float delta, float totalTime)
        {
            return delta * currTime / totalTime + initial;
        }

        float Sinusoidal::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            return -delta * Math::cos(currTime / totalTime * Math::HALF_PI) + delta + initial;
        }

        float Sinusoidal::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            return delta * Math::sin(currTime / totalTime * Math::HALF_PI) + initial;
        }

        float Sinusoidal::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            return -delta / 2.0f * (Math::cos(Math::PI * currTime / totalTime) - 1.0f) + initial;
        }

        float Quadratic::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return delta * currTime * currTime + initial;
        }

        float Quadratic::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return -delta * currTime * (currTime - 2.0f) + initial;
        }

        float Quadratic::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return delta / 2.0f * currTime * currTime + initial;

            currTime--;
            return -delta / 2.0f * (currTime * (currTime - 2.0f) - 1.0f) + initial;
        }

        float Cubic::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return delta * currTime * currTime * currTime + initial;
        }

        float Cubic::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            currTime--;
            return delta * (currTime * currTime * currTime + 1.0f) + initial;
        }

        float Cubic::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return delta / 2.0f * currTime * currTime * currTime + initial;

            currTime -= 2.0f;
            return delta / 2.0f * (currTime * currTime * currTime + 2.0f) + initial;
        }

        float Quartic::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return delta * currTime * currTime * currTime * currTime + initial;
        }

        float Quartic::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            currTime--;
            return -delta * (currTime * currTime * currTime * currTime - 1.0f) + initial;
        }

        float Quartic::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return delta / 2.0f * currTime * currTime * currTime * currTime + initial;

            currTime -= 2.0f;
            return -delta / 2.0f * (currTime * currTime * currTime * currTime - 2.0f) + initial;
        }

        float Quintic::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return delta * currTime * currTime * currTime * currTime * currTime + initial;
        }

        float Quintic::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            currTime--;
            return delta * (currTime * currTime * currTime * currTime * currTime + 1.0f) + initial;
        }

        float Quintic::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return delta / 2.0f * currTime * currTime * currTime * currTime * currTime + initial;

            currTime -= 2.0f;
            return delta / 2.0f * (currTime * currTime * currTime * currTime * currTime + 2.0f) + initial;
        }

        float Exponential::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            return (currTime == 0.0f) ? initial : delta * Math::pow(2.0f, 10.0f * (currTime / totalTime - 1.0f)) + initial;
        }

        float Exponential::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            return (currTime == totalTime) ? initial + delta : delta * (-Math::pow(2.0f, -10.0f * currTime / totalTime) + 1.0f) + initial;
        }

        float Exponential::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            if (currTime == 0)
                return initial;

            if (currTime == totalTime)
                return initial + delta;

            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return delta / 2.0f * (float)Math::pow(2.0f, 10.0f * (currTime - 1.0f)) + initial;

            currTime--;
            return delta / 2.0f * (float)(-Math::pow(2.0f, -10.0f * currTime) + 2.0f) + initial;
        }

        float Circular::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return -delta * (Math::sqrt(1.0f - currTime * currTime) - 1.0f) + initial;
        }

        float Circular::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            currTime--;
            return delta * Math::sqrt(1.0f - currTime * currTime) + initial;
        }

        float Circular::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return -delta / 2.0f * (Math::sqrt(1.0f - currTime * currTime) - 1.0f) + initial;

            currTime -= 2.0f;
            return delta / 2.0f * (Math::sqrt(1.0f - currTime * currTime) + 1.0f) + initial;
        }

        float Back::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            return delta * currTime * currTime * ((1.70158f + 1.0f) * currTime - 1.70158f) + initial;
        }

        float Back::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime = currTime / totalTime - 1.0f;
            return delta * (currTime * currTime * ((1.70158f + 1.0f) * currTime + 1.70158f) + 1.0f) + initial;
        }

        float Back::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            float s = 1.70158f * 1.525f;
            currTime /= totalTime / 2.0f;
            if (currTime < 1.0f)
                return delta / 2.0f * (currTime * currTime * ((s + 1.0f) * currTime - s)) + initial;

            currTime -= 2.0f;
            return delta / 2.0f * (currTime * currTime * ((s + 1.0f) * currTime + s) + 2.0f) + initial;
        }

        float Elastic::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            if (currTime == 0.0f)
                return initial;

            currTime /= totalTime;
            if (currTime == 1.0f)
                return initial + delta;

            float p = totalTime * 0.3f;
            float s = p / 4.0f;
            currTime--;
            return -(delta * Math::pow(2.0f, 10.0f * currTime) * Math::sin((currTime * totalTime - s) * 2.0f * Math::PI / p)) + initial;
        }

        float Elastic::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            if (currTime == 0.0f)
                return initial;

            currTime /= totalTime;
            if (currTime == 1.0f)
                return initial + delta;

            float p = totalTime * 0.3f;
            float s = p / 4.0f;
            return delta * Math::pow(2.0f, -10.0f * currTime) * Math::sin((currTime * totalTime - s) * 2.0f * Math::PI / p) + delta + initial;
        }

        float Elastic::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            if (currTime == 0.0f)
                return initial;

            currTime /= totalTime / 2.0f;
            if (currTime == 2.0f)
                return initial + delta;

            float p = totalTime * (0.3f * 1.5f);
            float a = delta;
            float s = p / 4.0f;
            currTime--;
            if (currTime < 1.0f)
                return -0.5f * a * Math::pow(2.0f, 10.0f * currTime) * Math::sin((currTime * totalTime - s) * 2.0f * Math::PI / p) + initial;

            return a * Math::pow(2.0f, -10.0f * currTime) * Math::sin((currTime * totalTime - s) * 2.0f * Math::PI / p) / 2.0f + delta + initial;
        }

        float Bounce::easeIn(float currTime, float initial, float delta, float totalTime)
        {
            return delta - easeOut(totalTime - currTime, 0.0f, delta, totalTime) + initial;
        }

        float Bounce::easeOut(float currTime, float initial, float delta, float totalTime)
        {
            currTime /= totalTime;
            if (currTime < (1.0f / 2.75f))
                return delta * (7.5625f * currTime * currTime) + initial;
            else if (currTime < (2.0f / 2.75f))
            {
                currTime -= (1.5f / 2.75f);
                return delta * (7.5625f * currTime * currTime + 0.75f) + initial;
            }
            else if (currTime < (2.5f / 2.75f))
            {
                currTime -= (2.25f / 2.75f);
                return delta * (7.5625f * currTime * currTime + 0.9375f) + initial;
            }
            else
            {
                currTime -= (2.625f / 2.75f);
                return delta * (7.5625f * currTime * currTime + 0.984375f) + initial;
            }
        }

        float Bounce::easeInOut(float currTime, float initial, float delta, float totalTime)
        {
            if (currTime < totalTime / 2.0f)
                return easeIn(currTime * 2.0f, 0.0f, delta, totalTime) / 2.0f + initial;
            
            return easeOut(currTime * 2.0f - totalTime, 0.0f, delta, totalTime) / 2.0f + delta / 2.0f + initial;
        }
    }
}