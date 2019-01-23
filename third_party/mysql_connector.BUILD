cc_library(
    name = "mysql_connector",
    srcs =glob( [
        "mysql-connector/lib64/*.so",
    ]),
    hdrs = glob([
        "mysql-connector/include/jdbc/cppconn/*.h",
    ]),
    # hdrs = ["mysql-connector/include/jdbc/cppconn/driver.h"],
    includes = [
        "mysql-connector/include/jdbc/cppconn/",
    ],
    # include_prefix = "third_party/mysql-connector/include/jdbc/cppconn",
    linkstatic = 0,
    visibility = [
        "//visibility:public",
    ],
)
