#include "net_janrupf_ujr_core_platform_abstraction_config_UlConfig_native_access.hpp"
#include "net_janrupf_ujr_core_platform_abstraction_config_UlFaceWinding_native_access.hpp"
#include "net_janrupf_ujr_core_platform_abstraction_config_UlFontHinting_native_access.hpp"
#include "net_janrupf_ujr_platform_jni_impl_JNIUlPlatform.h"

#include <Ultralight/platform/Config.h>

#include "ujr/util/JniEntryGuard.hpp"

JNIEXPORT void JNICALL
Java_net_janrupf_ujr_platform_jni_impl_JNIUlPlatform_nativeSetConfig(JNIEnv *env, jobject, jobject config) {
    ujr::jni_entry_guard(env, [&](auto env) {
        using ujr::native_access::UlConfig;
        using ujr::native_access::UlFaceWinding;
        using ujr::native_access::UlFontHinting;

        // Check that the config object is not null
        env.wrap_argument(config).require_non_null_argument("config");

        // Begin the translation
        ultralight::Config native_config;

        native_config.cache_path
            = UlConfig::CACHE_PATH.get(env, config).require_non_null_argument("config.cachePath").to_utf16();
        native_config.resource_path_prefix = UlConfig::RESOURCE_PATH_PREFIX.get(env, config)
                                                 .require_non_null_argument("config.resourcePathPrefix")
                                                 .to_utf16();

        auto face_winding = UlConfig::FACE_WINDING.get(env, config).require_non_null_argument("config.faceWinding");
        if (face_winding == UlFaceWinding::CLOCKWISE.get(env)) {
            native_config.face_winding = ultralight::FaceWinding::Clockwise;
        } else if (face_winding == UlFaceWinding::COUNTER_CLOCKWISE.get(env)) {
            native_config.face_winding = ultralight::FaceWinding::CounterClockwise;
        } else {
            throw std::runtime_error("Unexpected face winding value");
        }

        auto font_hinting = UlConfig::FONT_HINTING.get(env, config).require_non_null_argument("config.fontHinting");
        if (font_hinting == UlFontHinting::SMOOTH.get(env)) {
            native_config.font_hinting = ultralight::FontHinting::Smooth;
        } else if (font_hinting == UlFontHinting::NORMAL.get(env)) {
            native_config.font_hinting = ultralight::FontHinting::Normal;
        } else if (font_hinting == UlFontHinting::MONOCHROME.get(env)) {
            native_config.font_hinting = ultralight::FontHinting::Monochrome;
        } else if (font_hinting == UlFontHinting::NONE.get(env)) {
            native_config.font_hinting = ultralight::FontHinting::None;
        } else {
            throw std::runtime_error("Unexpected font hinting value");
        }
    });
}
