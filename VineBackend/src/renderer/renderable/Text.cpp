#include <vine/renderer/renderable/Text.h>

#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceFont.h>
#include <vine/core/Logger.h>

namespace vine
{
    Text::Text(const Handle& fontHandle, const TextState& state)
        : Renderable(state), fontHandle_(fontHandle), text_(state.text), kerning_(state.kerning), lineSpacing_(state.lineSpacing)
    {
        ResourceFont* resFont = ResourceManager::ref().getResource<ResourceFont>(fontHandle_);
        DBG_ASSERT(resFont, "Font resource with given handle could not be found");

        if (!resFont->isLoaded())
            resFont->load();

        font_ = resFont->getFont();
        setShader("TextShader");
    }

    Text::~Text()
    {
    }

    void Text::render() const
    {
        Renderer::ref().drawText(text_, font_, getTransform(), { getColor(), kerning_, lineSpacing_ });
    }
}