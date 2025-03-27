#include <vine/resource/ResourceFont.h>

#include <vine/resource/ResourceManager.h>
#include <vine/core/Logger.h>

#include <vector>

#undef INFINITE
#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <msdf-atlas-gen/FontGeometry.h>
#include <msdf-atlas-gen/GlyphGeometry.h>

namespace vine
{
    struct MSDFData
    {
        std::vector<msdf_atlas::GlyphGeometry> glyphs;
        msdf_atlas::FontGeometry fontGeometry;
    };

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
        spec.format = ImageFormat::RGBA8;
        spec.generateMips = false;

        TextureSamplerSettings settings;
        settings.minFilter = settings.magFilter = TextureFilterMode::Linear;

        Ref<ResourceImage> tex = ResourceImage::createFromBytes((void*)bitmap.pixels, fontName, spec, settings);
        return tex;
    }

    ResourceFont::ResourceFont(const ResourceCreationData& data)
        : Resource(data), data_(new MSDFData()), fontSize_(1.0f)
    {
    }

    ResourceFont::~ResourceFont()
    {
        unload();
    }

    void ResourceFont::reload()
    {
        if (loaded_)
            return;

        loaded_ = true;
    }

    void ResourceFont::unload()
    {
        if (!loaded_)
            return;

        atlasTexture_ = nullptr;
        delete data_;
        loaded_ = false;
    }

    void ResourceFont::loadFromFont()
    {
        const ResourceCreationData* data = getCreationData();

        msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
        DBG_ASSERT(ft, "Freetype could not be initialized");

        msdfgen::FontHandle* font = msdfgen::loadFont(ft, data->file.c_str());
        if (!font)
        {
            DBG_ERROR("Failed to load font: {0}", data->file.c_str());
            return;
        }

        struct CharsetRange
        {
            uint32_t begin;
            uint32_t end;
        };

        static const CharsetRange ranges[] = { {0x0020, 0x00FF} };
        msdf_atlas::Charset charset;
        for (auto range : ranges)
        {
            for (uint32_t c = range.begin; c <= range.end; c++)
                charset.add(c);
        }

        double fontScale = 1.0;
        data_->fontGeometry = msdf_atlas::FontGeometry(&data_->glyphs);
        int glyphsLoaded = data_->fontGeometry.loadCharset(font, fontScale, charset);
        DBG_INFO("Loaded {0} glyphs from font (out of {1})", glyphsLoaded, charset.size());

        double emSize = 40.0;
        msdf_atlas::TightAtlasPacker atlasPacker;
        atlasPacker.setMiterLimit(1.0);
        atlasPacker.setSpacing(0);
        atlasPacker.setScale(emSize);
        atlasPacker.setUnitRange(0.2);

        DBG_INFO("Atlas px range: {0}, {1}", atlasPacker.getPixelRange().lower, atlasPacker.getPixelRange().upper);

        int remaining = atlasPacker.pack(data_->glyphs.data(), (int)data_->glyphs.size());
        DBG_ASSERT(remaining == 0, "");

        int width, height;
        atlasPacker.getDimensions(width, height);
        emSize = atlasPacker.getScale();

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8

        uint64_t coloringSeed = 0;
        bool expensiveColoring = false;

        if (expensiveColoring)
        {
            msdf_atlas::Workload([&glyphs = data_->glyphs, &coloringSeed](int i, int threadNo) -> bool
                {
                    unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
                    glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
                    return true;
                },
                data_->glyphs.size()).finish(THREAD_COUNT);
        }
        else
        {
            unsigned long long glyphSeed = coloringSeed;
            for (auto& glyph : data_->glyphs)
            {
                glyphSeed *= LCG_MULTIPLIER;
                glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
            }
        }

        atlasTexture_ = createAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>("tex_" + data->file, (float)emSize, data_->glyphs, data_->fontGeometry, width, height);
        msdfgen::destroyFont(font);
        msdfgen::deinitializeFreetype(ft);
    }

    Ref<ResourceFont> ResourceFont::create(const std::string& file)
    {
        ResourceCreationData data = ResourceCreationData(file);
        data.type = ResourceDataType::ResourceDataTypeFont;
        ResourceFont* res = dynamic_cast<ResourceFont*>(ResourceManager::ref().get(data));
        
        if (!res)
        {
            res = new ResourceFont(data);
            res->loadFromFont();
        }

        return Ref<ResourceFont>(res);
    }
}