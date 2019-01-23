cc_library(
    name = "curl",
    srcs =glob( [
        "curl/lib/*.so",
    ]),
    hdrs = glob([
        "curl/include/**/*.h",
    ]),
    includes = [
        "curl/include/",
    ],
    linkstatic = 0,
    visibility = [
        "//visibility:public",
    ],
)
