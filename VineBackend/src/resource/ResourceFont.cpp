#include <vine/resource/ResourceFont.h>

#include <vector>

#undef INFINITE
#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <msdf-atlas-gen/FontGeometry.h>
#include <msdf-atlas-gen/GlyphGeometry.h>

namespace vine
{

    template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
    static Ref<ResourceImage> createAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
        const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height)
    {
        msdf_atlas::GeneratorAttributes attributes;
        attributes.config.overlapSupport = true;
        attributes.scanlinePass = true;

        msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
        generator.setAttributes(attributes);
        generator.setThreadCount(8);
        generator.generate(glyphs.data(), (int)glyphs.size());

        msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();

        TextureSpecification spec;
        spec.width = bitmap.width;
        spec.height = bitmap.height;
        spec.format = ImageFormat::RGB8;
        spec.generateMips = false;

        TextureRef tex = createRef<Texture>(spec);
        tex->setData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);
        return tex;
    }

    struct MSDFData
    {
        std::vector<msdf_atlas::GlyphGeometry> glyphs;
        msdf_atlas::FontGeometry fontGeometry;
    };

    ResourceFont::ResourceFont(const ResourceCreationData& data)
        : Resource(data)
    {
        //creationData_->type = ResourceDataType::ResourceDataTypeFont;
    }

    ResourceFont::~ResourceFont()
    {
        unload();
    }

    void ResourceFont::load()
    {
        if (loaded_)
            return;

        loaded_ = true;
    }

    void ResourceFont::unload()
    {
        if (!loaded_)
            return;

        loaded_ = false;
    }
}