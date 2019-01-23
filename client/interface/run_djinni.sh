#! /usr/bin/env bash

base_dir=$(cd "`dirname "0"`" && pwd)
cpp_out="$base_dir/../native/cpp"
jni_out="$base_dir/../android/account/app/src/main/cpp/jni"
java_out="$base_dir/../android/account/app/src/main/java/me/ppxpp/account/auth/"
java_package="me.ppxpp.account.auth"
namespace="act"
djinni_file="auth.djinni"

../../third_party/djinni/src/run \
	--java-out $java_out \
	--java-package $java_package \
	--ident-java-field mFooBar \
	\
	--cpp-out $cpp_out \
	--cpp-namespace $namespace \
	\
	--jni-out $jni_out \
	--ident-jni-class native_foo_bar \
	--ident-jni-file native_foo_bar \
	\
	--idl $djinni_file
