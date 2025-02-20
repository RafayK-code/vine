#include <vine/renderer/renderable/Text.h>

#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceFont.h>
#include <vine/core/Logger.h>

#undef INFINITE
#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <msdf-atlas-gen/FontGeometry.h>
#include <msdf-atlas-gen/GlyphGeometry.h>

#include <sstream>

namespace vine
{
    struct MSDFData
    {
        std::vector<msdf_atlas::GlyphGeometry> glyphs;
        msdf_atlas::FontGeometry fontGeometry;
    };

    static std::vector<std::string> split(const std::string& str, char delimiter)
    {
        std::vector<std::string> res;
        std::stringstream ss;
        std::string token;

        while (std::getline(ss, token, delimiter))
            res.push_back(token);

        return res;
    }

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

    void Text::processText()
    {
        chunks_.clear();
        std::vector<std::string> lines = split(text_, '\n');
        for (const auto& str : lines)
            chunks_.push_back(processLine(str));
    }

    Text::Chunk Text::processLine(const std::string& line) const
    {
        const msdf_atlas::FontGeometry& fontGeomtry = font_->getData()->fontGeometry;
        const msdfgen::FontMetrics& metrics = fontGeomtry.getMetrics();
        Ref<ResourceImage> fontAtlas = font_->getAtlasTexture();

        double x = 0.0;
        double fsScale = font_->getFontSize() / (metrics.ascenderY - metrics.descenderY);
        double y = 0.0;

        const float spaceGlyphAdvance = fontGeomtry.getGlyph(' ')->getAdvance();

        for (size_t i = 0; i < line.size(); i++)
        {
            char character = line[i];
            if (character == '\r')
                continue;

            if (character == ' ')
            {
                float advance = spaceGlyphAdvance;
                if (i < line.size() - 1)
                {
                    char nextCharacter = line[i + 1];
                    double dAdvance;
                    fontGeomtry.getAdvance(dAdvance, character, nextCharacter);
                    advance = (float)dAdvance;
                }

                x += fsScale * advance + kerning_;
                continue;
            }

            if (character == '\t')
            {
                x += 4.0f * (fsScale * spaceGlyphAdvance + kerning_);
                continue;
            }

            const msdf_atlas::GlyphGeometry* glyph = fontGeomtry.getGlyph(character);
            if (!glyph)
                glyph = fontGeomtry.getGlyph('?');


            double advance = glyph->getAdvance();
            if (i < line.size() - 1)
            {
                char nextCharacter =  line[i + 1] ;
                fontGeomtry.getAdvance(advance, character, nextCharacter);
            }

            x += fsScale * advance + kerning_;
        }

        float width = (float)x;
        Chunk chunk = { line, width };
        return chunk;
    }
}