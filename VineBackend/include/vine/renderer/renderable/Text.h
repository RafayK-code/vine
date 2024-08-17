#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/backend/Font.h>

#include <string>

namespace vine
{
    struct TextState : public RenderableState
    {
        std::string text = "";
        float kerning = 0.0f;
        float lineSpacing = 0.0f;
    };

    class Text : public Renderable
    {
    public:
        Text(const std::string& fontPath, const TextState& state);
        Text(const FontRef& font, const TextState& state);

        virtual ~Text();

        virtual void render() const;

        const std::string& getText() const { return text_; }
        void setText(const std::string& text) { text_ = text; }

        float getKerning() const { return kerning_; }
        void setKerning(float kerning) { kerning_ = kerning; }

        float getLineSpacing() const { return lineSpacing_; }
        float setLineSpacing(float lineSpacing) { lineSpacing_ = lineSpacing; }

        const FontRef& getFont() const { return font_; }

    private:
        std::string text_;
        float kerning_;
        float lineSpacing_;

        FontRef font_;
    };
}