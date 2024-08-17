#pragma once

#include <vector>

#undef INFINITE
#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace vine
{
    struct MSDFData
    {
        std::vector<msdf_atlas::GlyphGeometry> glyphs;
        msdf_atlas::FontGeometry fontGeometry;
    };
}