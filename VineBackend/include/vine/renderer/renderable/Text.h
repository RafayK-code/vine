#pragma once

#include <vine/renderer/renderable/Renderable.h>
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
        Text(const std::string& fontfile, const TextState& state);
        virtual ~Text();

        virtual void render() const override;
        virtual Ref<Renderable> clone() const override;

        const std::string& getText() const { return text_; }
        void setText(const std::string& text) { text_ = text; }

        float getKerning() const { return kerning_; }
        void setKerning(float kerning) { kerning_ = kerning; }

        float getLineSpacing() const { return lineSpacing_; }
        void setLineSpacing(float lineSpacing) { lineSpacing_ = lineSpacing; }

        const Ref<ResourceFont>& getFont() const { return font_; }

    private:
        std::string text_;
        float kerning_;
        float lineSpacing_;

        Ref<ResourceFont> font_;
    };
}