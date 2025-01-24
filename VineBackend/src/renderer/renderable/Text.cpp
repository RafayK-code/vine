#include <vine/renderer/renderable/Text.h>

#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceFont.h>
#include <vine/core/Logger.h>

namespace vine
{
    Text::Text(const std::string& fontfile, const TextState& state)
        : Renderable(state), text_(state.text), kerning_(state.kerning), lineSpacing_(state.lineSpacing)
    {
        font_ = ResourceFont::create(fontfile);
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