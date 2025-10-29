#pragma once

#include "draw_msaa_image_mesh.frag.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char draw_msaa_image_mesh_frag[] = R"===(/*
 * Copyright 2023 Rive
 */

#ifdef _EXPORTED_FRAGMENT

FRAG_TEXTURE_BLOCK_BEGIN
TEXTURE_RGBA8(PER_DRAW_BINDINGS_SET, IMAGE_TEXTURE_IDX, _EXPORTED_imageTexture);
#ifdef _EXPORTED_ENABLE_ADVANCED_BLEND
DST_COLOR_TEXTURE(_EXPORTED_dstColorTexture);
#endif
FRAG_TEXTURE_BLOCK_END

DYNAMIC_SAMPLER_BLOCK_BEGIN
SAMPLER_DYNAMIC(PER_DRAW_BINDINGS_SET, IMAGE_SAMPLER_IDX, imageSampler)
DYNAMIC_SAMPLER_BLOCK_END

FRAG_STORAGE_BUFFER_BLOCK_BEGIN
FRAG_STORAGE_BUFFER_BLOCK_END

FRAG_DATA_MAIN(half4, _EXPORTED_drawFragmentMain)
{
    VARYING_UNPACK(v_texCoord, float2);

    half4 color = TEXTURE_SAMPLE_DYNAMIC_LODBIAS(_EXPORTED_imageTexture,
                                                 imageSampler,
                                                 v_texCoord,
                                                 uniforms.mipMapLODBias) *
                  imageDrawUniforms.opacity;

#if defined(_EXPORTED_ENABLE_ADVANCED_BLEND) && !defined(_EXPORTED_FIXED_FUNCTION_COLOR_OUTPUT)
    if (_EXPORTED_ENABLE_ADVANCED_BLEND)
    {
        // Do the color portion of the blend mode in the shader.
        half4 dstColorPremul = DST_COLOR_FETCH(_EXPORTED_dstColorTexture);
        color.xyz = advanced_color_blend(unmultiply_rgb(color),
                                         dstColorPremul,
                                         imageDrawUniforms.blendMode);
        // Src-over blending is enabled, so just premultiply and let the HW
        // finish the the the alpha portion of the blend mode.
        color.xyz *= color.w;
    }
#endif // @ENABLE_ADVANCED_BLEND && !@FIXED_FUNCTION_COLOR_OUTPUT

    EMIT_FRAG_DATA(color);
}

#endif // @FRAGMENT
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive