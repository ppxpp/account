// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from auth.djinni

#pragma once

#include "auth.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class native_auth final : ::djinni::JniInterface<::act::Auth, native_auth> {
public:
    using CppType = std::shared_ptr<::act::Auth>;
    using CppOptType = std::shared_ptr<::act::Auth>;
    using JniType = jobject;

    using Boxed = native_auth;

    ~native_auth();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<native_auth>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<native_auth>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    native_auth();
    friend ::djinni::JniClass<native_auth>;
    friend ::djinni::JniInterface<::act::Auth, native_auth>;

};

}  // namespace djinni_generated