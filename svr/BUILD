# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "server",
    srcs = ["server.cc", 
            "service/AccountService.h",
            "service/AccountService.cpp",
			"data/AccountDb.h",
			"data/AccountDb.cpp",
			"utils/Encrypt.h",
			"utils/Encrypt.cpp",
			"utils/md5.h",
			"utils/md5.cpp",
			"utils/Push.h",
			"utils/Push.cpp",
            "auth.impl.h",
            "auth.impl.cc",
            "auth.grpc.pb.cc", 
            "auth.pb.cc", 
            "auth.grpc.pb.h", 
            "auth.pb.h"],
    deps = ["@com_github_grpc_grpc//:grpc++", 
			"@com_github_grpc_grpc//:grpc_plugin_support", 
			"@mysql_connector//:mysql_connector",
			"@acl_cpp//:acl_cpp",
			"@curl//:curl"],
)

# cc_binary(
#    name = "client",
#    srcs = ["client.cc", "auth.grpc.pb.cc", "auth.pb.cc", "auth.grpc.pb.h", "auth.pb.h"],
#    deps = ["@com_github_grpc_grpc//:grpc++", "@com_github_grpc_grpc//:grpc_plugin_support"]
# )