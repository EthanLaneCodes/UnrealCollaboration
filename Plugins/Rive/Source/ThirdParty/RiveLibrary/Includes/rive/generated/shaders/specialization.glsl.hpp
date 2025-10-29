#pragma once

#include "specialization.glsl.exports.h"

namespace rive {
namespace gpu {
namespace glsl {
const char specialization[] = R"===(#ifndef _EXPORTED_SPEC_CONST_NONE

layout(constant_id = CLIPPING_SPECIALIZATION_IDX) const
    bool kEnableClipping = true;
layout(constant_id = CLIP_RECT_SPECIALIZATION_IDX) const
    bool kEnableClipRect = true;
layout(constant_id = ADVANCED_BLEND_SPECIALIZATION_IDX) const
    bool kEnableAdvancedBlend = true;
layout(constant_id = FEATHER_SPECIALIZATION_IDX) const
    bool kEnableFeather = true;
layout(constant_id = EVEN_ODD_SPECIALIZATION_IDX) const
    bool kEnableEvenOdd = true;
layout(constant_id = NESTED_CLIPPING_SPECIALIZATION_IDX) const
    bool kEnableNestedClipping = true;
layout(constant_id = HSL_BLEND_MODES_SPECIALIZATION_IDX) const
    bool kEnableHSLBlendModes = true;
layout(constant_id = CLOCKWISE_FILL_SPECIALIZATION_IDX) const
    bool kClockwiseFill = true;
layout(constant_id = BORROWED_COVERAGE_PREPASS_SPECIALIZATION_IDX) const
    bool kBorrowedCoveragePrepass = true;
layout(constant_id = VULKAN_VENDOR_ID_SPECIALIZATION_IDX) const uint
    kVulkanVendorID = 0;

#define _EXPORTED_ENABLE_CLIPPING  kEnableClipping

// MSAA uses gl_ClipDistance when ENABLE_CLIP_RECT is set, but since Vulkan is
// using specialization constants (as opposed to compile-time flags), it means
// that the usage of them is in the compiled shader even if that codepath is
// not going to be taken, which ends up as a validation failure on systems that
// do not support that extension. In those cases, we can just not define
// ENABLE_CLIP_RECT to avoid all of the gl_ClipDistance usages.
#ifndef _EXPORTED_DISABLE_CLIP_RECT_FOR_VULKAN_MSAA
#define _EXPORTED_ENABLE_CLIP_RECT  kEnableClipRect
#endif

#define _EXPORTED_ENABLE_ADVANCED_BLEND  kEnableAdvancedBlend
#define _EXPORTED_ENABLE_FEATHER  kEnableFeather
#define _EXPORTED_ENABLE_EVEN_ODD  kEnableEvenOdd
#define _EXPORTED_ENABLE_NESTED_CLIPPING  kEnableNestedClipping
#define _EXPORTED_ENABLE_HSL_BLEND_MODES  kEnableHSLBlendModes
#define _EXPORTED_CLOCKWISE_FILL  kClockwiseFill
#define _EXPORTED_BORROWED_COVERAGE_PREPASS  kBorrowedCoveragePrepass
#define _EXPORTED_VULKAN_VENDOR_ID  kVulkanVendorID

#else

// Specialization constants aren't supported; just compile an ubershader.
#define _EXPORTED_ENABLE_CLIPPING  true
#define _EXPORTED_ENABLE_CLIP_RECT  true
#define _EXPORTED_ENABLE_ADVANCED_BLEND  true
#define _EXPORTED_ENABLE_FEATHER  true
#define _EXPORTED_ENABLE_EVEN_ODD  true
#define _EXPORTED_ENABLE_NESTED_CLIPPING  true
#define _EXPORTED_ENABLE_HSL_BLEND_MODES  true
#define _EXPORTED_CLOCKWISE_FILL  true
#define _EXPORTED_BORROWED_COVERAGE_PREPASS  true
#define _EXPORTED_VULKAN_VENDOR_ID  0

#endif
)===";
} // namespace glsl
} // namespace gpu
} // namespace rive