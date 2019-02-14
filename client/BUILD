# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "client",
    srcs = ["client.cc", 
            "auth_client.cpp",
            "auth_client.hpp",
            "auth.grpc.pb.cc", 
            "auth.pb.cc", 
            "auth.grpc.pb.h", 
            "auth.pb.h"],
    deps = ["@com_github_grpc_grpc//:grpc++", "@com_github_grpc_grpc//:grpc_plugin_support"]
)