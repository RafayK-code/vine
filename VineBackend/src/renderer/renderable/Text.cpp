#include <vine/renderer/renderable/Text.h>

#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceFont.h>
#include <vine/core/Logger.h>

namespace vine
{
    Text::Text(const ResourceHandle& fontHandle, const TextState& state)
        : Renderable(state), text_(state.text), kerning_(state.kerning), lineSpacing_(state.lineSpacing)
    {
        res_ = ResourceManager::ref().getResource<ResourceFont>(fontHandle);
        DBG_ASSERT(res_, "Font resource with given handle could not be found");

        if (!res_->isLoaded())
            res_->load();

        font_ = res_->getFont();
        setShader("TextShader");
    }

    Text::~Text()
    {
    }

    void Text::render() const
    {
        Renderer::ref().drawText(text_, font_, getTransform(), { getColor(), kerning_, lineSpacing_ });
    }

    Renderable* Text::clone() const
    {
        return new Text(*this);
    }
}