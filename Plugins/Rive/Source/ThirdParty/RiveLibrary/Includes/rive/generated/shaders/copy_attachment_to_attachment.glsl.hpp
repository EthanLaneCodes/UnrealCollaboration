#pragma once

#include "copy_attachment_to_attachment.glsl.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char copy_attachment_to_attachment[] = R"===(/*
 * Copyright 2025 Rive
 */

#ifdef _EXPORTED_VERTEX
void main()
{
    // Fill the entire screen. The caller will use a scissor test to control the
    // bounds being drawn.
    gl_Position.x = (gl_VertexID & 1) == 0 ? -1. : 1.;
    gl_Position.y = (gl_VertexID & 2) == 0 ? -1. : 1.;
    gl_Position.z = 0.;
    gl_Position.w = 1.;
}
#endif

#ifdef _EXPORTED_FRAGMENT
layout(input_attachment_index = 0,
       // TODO: This shader is currently only used by MSAA to seed the color
       // buffer, so we do the easy thing and bind to MSAA_COLOR_SEED_IDX.
       // In the future we may need to set up new bindings for this input
       // attachment.
       binding = MSAA_COLOR_SEED_IDX,
       set = PLS_TEXTURE_BINDINGS_SET) uniform lowp subpassInput
    inputAttachment;

layout(location = 0) out half4 outputColor;

void main() { outputColor = subpassLoad(inputAttachment); }
#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive