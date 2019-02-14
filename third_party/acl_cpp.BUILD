cc_library(
    name = "acl_cpp",
    srcs =glob( [
        "acl/libacl_all.a",
    ]),
    hdrs = glob([
        "acl/lib_acl/include/**/*.h",
        "acl/lib_acl_cpp/include/**/*.hpp",
		"acl/lib_acl_cpp/include/**/*.ipp",
    ]),
    includes = [
        "acl/lib_acl_cpp/include",
		"acl/lib_acl/include",
		"acl/lib_protocol/include",
		"acl/include",
    ],
    linkstatic = 0,
    visibility = [
        "//visibility:public",
    ],
)
