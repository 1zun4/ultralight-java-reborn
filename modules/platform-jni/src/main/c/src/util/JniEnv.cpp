#include "ujr/util/JniEnv.hpp"

#include <utility>

namespace ujr {
    JavaVM *JniEnv::jvm = nullptr;

    JniEnv::JniEnv(JNIEnv *env)
        : env(env) {}

    JniEnv::JniEnv(const JniEnv &other)
        : env(other.env) {}

    JniEnv::JniEnv(JniEnv &&other) noexcept
        : env(other.env) {
        other.env = nullptr;
    }

    JniEnv &JniEnv::operator=(const JniEnv &other) {
        if (&other != this) {
            this->env = other.env;
        }

        return *this;
    }

    JniEnv &JniEnv::operator=(JniEnv &&other) noexcept {
        this->env = other.env;
        other.env = nullptr;

        return *this;
    }

    void JniEnv::init(JavaVM *jvm) { JniEnv::jvm = jvm; }

    void JniEnv::deinit() { JniEnv::jvm = nullptr; }

    JniEnv JniEnv::from_existing(JNIEnv *env) { return std::move(JniEnv(env)); }

    JniEnv JniEnv::from_thread(bool auto_attach) {
        JNIEnv *env;

        auto result = jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_8);
        if (result == JNI_EDETACHED) {
            if (auto_attach) {
                // Automatically attach the thread to the JVM
                jvm->AttachCurrentThread(reinterpret_cast<void **>(&env), nullptr);
            } else {
                // Not attached and not allowed to attach, return an invalid environment
                return std::move(JniEnv(nullptr));
            }
        }

        // The JNI environment should be valid at this point
        return std::move(JniEnv(env));
    }

    bool JniEnv::is_valid() const { return env != nullptr; }

    JNIEnv *JniEnv::get() const { return env; }

    JNIEnv *JniEnv::operator->() const { return get(); }
} // namespace ujr