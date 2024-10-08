#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/backend/Font.h>

#include <string>
#include <crossguid/guid.hpp>

namespace vine
{
    using Handle = xg::Guid;

    struct TextState : public RenderableState
    {
        std::string text = "";
        float kerning = 0.0f;
        float lineSpacing = 0.0f;
    };

    class Text : public Renderable
    {
    public:
        Text(const Handle& fontHandle, const TextState& state);
        virtual ~Text();

        virtual void render() const;

        const std::string& getText() const { return text_; }
        void setText(const std::string& text) { text_ = text; }

        float getKerning() const { return kerning_; }
        void setKerning(float kerning) { kerning_ = kerning; }

        float getLineSpacing() const { return lineSpacing_; }
        void setLineSpacing(float lineSpacing) { lineSpacing_ = lineSpacing; }

        const FontRef& getFont() const { return font_; }
        const Handle& getFontHandle() const { return fontHandle_; }

    private:
        std::string text_;
        float kerning_;
        float lineSpacing_;

        FontRef font_;
        Handle fontHandle_;
    };
}