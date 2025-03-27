#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/resource/ResourceFont.h>

#include <string>

namespace vine
{
    enum class TextAlignment
    {
        Left,
        Centered,
        Right,
    };

    class Text : public Renderable
    {
    public:
        Text(const std::string& fontfile, const RenderableState& state, const std::string& text = "", float kerning = 0.0f, float lineSpacing = 0.0f);
        virtual ~Text();

        virtual void render() const override;
        virtual Ref<Renderable> clone() const override;

        const std::string& getText() const { return text_; }
        void setText(const std::string& text) { text_ = text; processText(); }

        float getKerning() const { return kerning_; }
        void setKerning(float kerning) { kerning_ = kerning; }

        float getLineSpacing() const { return lineSpacing_; }
        void setLineSpacing(float lineSpacing) { lineSpacing_ = lineSpacing; }

        TextAlignment getAlignment() const { return alignment_; }
        void setAlignmemnt(TextAlignment alignment) { alignment_ = alignment; processText(); }

        float getFontSize() const { return fontSize_; }
        void setFontSize(float fontSize) { fontSize_ = fontSize; }

        const Ref<ResourceFont>& getFont() const { return font_; }

    private:
        struct Chunk
        {
            std::string text;
            float width;
        };

        void processText();
        Chunk processLine(const std::string& line) const;

    private:
        std::string text_;
        float kerning_;
        float lineSpacing_;
        TextAlignment alignment_;

        float maxLineWidth_;
        float textHeight_;

        float fontSize_;

        std::vector<Chunk> chunks_;

        Ref<ResourceFont> font_;
    };
}