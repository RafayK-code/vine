#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/backend/Font.h>
#include <vine/resource/ResourceFont.h>

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
        Text(const ResourceHandle& fontHandle, const TextState& state);

        virtual ~Text();

        virtual void render() const override;
        virtual Renderable* clone() const override;

        const std::string& getText() const { return text_; }
        void setText(const std::string& text) { text_ = text; }

        float getKerning() const { return kerning_; }
        void setKerning(float kerning) { kerning_ = kerning; }

        float getLineSpacing() const { return lineSpacing_; }
        void setLineSpacing(float lineSpacing) { lineSpacing_ = lineSpacing; }

        const FontRef& getFont() const { return font_; }
        const ResourceFont* getResource() const { return res_; }

    private:
        std::string text_;
        float kerning_;
        float lineSpacing_;

        FontRef font_;
        ResourceFont* res_;
    };
}