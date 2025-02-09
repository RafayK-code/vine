#pragma once

#include <vine/tween/TweenChainItem.h>
#include <vine/tween/TweenChainConfig.h>

namespace vine
{
    using TweenList = std::vector<Ref<Tweenable>>;

    class TweenChain : public Tweenable
    {
    public:
        TweenChain(const TweenChainConfig& config = TweenChainConfig());
        virtual ~TweenChain();

        virtual void tick(float dt) override;

        virtual void complete() override;
        virtual void rewind(bool skipDelay = true) override;

        virtual void removeTweenProperty(TweenProperty* property) override;
        virtual bool containsTweenProperty(TweenProperty* property) const override;
        virtual void getTweenProperties(TweenProperties& list) const override;

        TweenChain& append(Tweenable* tween);
        TweenChain& appendDelay(float delay);
        TweenChain& prepend(Tweenable* tween);
        TweenChain& prependDelay(float delay);

    protected:
        void append(const TweenChainItem& item);
        void prepend(const TweenChainItem& item);

    private:
        using ChainItems = std::vector<TweenChainItem>;
        ChainItems tweenItems_;

        TweenProperties properties_;
    };
}