#pragma once

#include <vine/renderer/renderable/builder/RenderableBuilder.h>

#include <vine/renderer/renderable/Text.h>

namespace vine
{
    class TextRenderableBuilder : public RenderableBuilderT<TextRenderableBuilder, Text>
    {
    public:
        TextRenderableBuilder(const std::string& fontFile);
        virtual ~TextRenderableBuilder();

        virtual Ref<Renderable> create() const override;

        TextRenderableBuilder& setFontFile(const std::string& fontFile);
        TextRenderableBuilder& setText(const std::string& text);
        TextRenderableBuilder& setKerning(float kerning);
        TextRenderableBuilder& setLineSpacing(float lineSpacing);

    private:
        std::string text_;
        float kerning_;
        float lineSpacing_;

        std::string fontFile_;
    };
}