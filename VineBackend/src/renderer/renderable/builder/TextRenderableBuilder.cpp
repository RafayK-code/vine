#include <vine/renderer/renderable/builder/TextRenderableBuilder.h>

namespace vine
{
    TextRenderableBuilder::TextRenderableBuilder(const std::string& fontFile)
        : fontFile_(fontFile), text_(""), kerning_(0.0f), lineSpacing_(0.0f)
    {
    }

    TextRenderableBuilder::~TextRenderableBuilder()
    {
    }

    Ref<Renderable> TextRenderableBuilder::create() const
    {
        return Ref<Text>(new Text(fontFile_, state_, text_, kerning_, lineSpacing_));
    }

    TextRenderableBuilder& TextRenderableBuilder::setFontFile(const std::string& fontFile)
    {
        fontFile_ = fontFile;
        return *this;
    }

    TextRenderableBuilder& TextRenderableBuilder::setText(const std::string& text)
    {
        text_ = text;
        return *this;
    }

    TextRenderableBuilder& TextRenderableBuilder::setKerning(float kerning)
    {
        kerning_ = kerning;
        return *this;
    }

    TextRenderableBuilder& TextRenderableBuilder::setLineSpacing(float lineSpacing)
    {
        lineSpacing_ = lineSpacing;
        return *this;
    }
}