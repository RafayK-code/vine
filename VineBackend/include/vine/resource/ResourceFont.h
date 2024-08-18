#pragma once

#include <vine/resource/Resource.h>
#include <vine/renderer/backend/Font.h>

namespace vine
{
    class ResourceFont : public Resource
    {
        friend class ResourceManager;
    public:
        ~ResourceFont();

        virtual void load() override;
        virtual void unload() override;

        FontRef getFont() const { return font_; }

    protected:
        ResourceFont(const ResourceCreationData& data);

    private:
        FontRef font_;
    };
}