#include <vine/renderer/renderable/Text.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    Text::Text(const std::string& fontPath, const TextState& state)
        : Renderable(state), text_(state.text), kerning_(state.kerning), lineSpacing_(state.lineSpacing)
    {
        font_ = std::make_shared<Font>(fontPath);
    }

    Text::Text(const FontRef& font, const TextState& state)
        : Renderable(state), font_(font), text_(state.text), kerning_(state.kerning), lineSpacing_(state.lineSpacing)
    {
    }

    Text::~Text()
    {
    }

    void Text::render() const
    {
        Renderer::ref().drawText(text_, font_, getTransform(), { getColor(), kerning_, lineSpacing_ });
    }
}