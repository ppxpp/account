load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/v1.18.0.tar.gz",
    ],
    strip_prefix = "grpc-1.18.0",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

http_archive(
    name = "com_google_protobuf",
    strip_prefix = "protobuf-3.6.1.3",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.6.1.3.tar.gz"],
)

new_local_repository(
    name = "mysql_connector",
    path = "third_party/",
    build_file = "third_party/mysql_connector.BUILD",
)

new_local_repository(
    name = "curl",
    path = "third_party/",
    build_file = "third_party/curl.BUILD",
)