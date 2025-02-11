#include <vine/renderer/renderable/Text.h>

#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceFont.h>
#include <vine/core/Logger.h>

namespace vine
{
    Text::Text(const std::string& fontfile, const RenderableState& state, const std::string& text, float kerning, float lineSpacing)
        : Renderable(state), text_(text), kerning_(kerning), lineSpacing_(lineSpacing)
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

    Ref<Renderable> Text::clone() const
    {
        return Ref<Text>(new Text(*this));
    }
}