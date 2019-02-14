// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from auth.djinni

#include "native_push_listener.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

native_push_listener::native_push_listener() : ::djinni::JniInterface<::act::PushListener, native_push_listener>() {}

native_push_listener::~native_push_listener() = default;

native_push_listener::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

native_push_listener::JavaProxy::~JavaProxy() = default;

void native_push_listener::JavaProxy::onNotify(const std::string & c_pushMsg) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::native_push_listener>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_onNotify,
                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c_pushMsg)));
    ::djinni::jniExceptionCheck(jniEnv);
}

}  // namespace djinni_generated