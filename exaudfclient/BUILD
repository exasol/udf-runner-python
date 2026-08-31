package(default_visibility = ["//visibility:public"])

load("//:variables.bzl", "VM_ENABLED_DEFINES")
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_shell//shell:sh_library.bzl", "sh_library")

config_setting(
    name = "python",
    define_values = {"python": "true"},
)

cc_binary(
    name = "exaudfclient_bin",
    srcs = [
        "exa_udfclient.cc",
        "exa_udf_client.cc",
        "exa_udf_client.h",
        "exa_vm_factory.cc",
        "exa_vm_factory.h",
        "@exaudfclient_base//:load_dynamic",
    ],
    linkopts = ["-ldl"],
    deps = [
        "//base/python/python3:pythoncontainer",
        "@exaudfclient_base//exa_udfclient_binary_common:exa_udfclient_binary_common_lib",
    ],
    defines = VM_ENABLED_DEFINES,
    data = ["@exaudfclient_base//:libexaudflib_complete.so"],
)

cc_binary(
    name = "exaudfclient_static_bin",
    srcs = [
        "exa_udfclient.cc",
        "exa_udf_client.cc",
        "exa_udf_client.h",
        "exa_vm_factory.cc",
        "exa_vm_factory.h",
        "@exaudfclient_base//:load_dynamic",
    ],
    linkopts = ["-ldl"],
    deps = [
        "//base/python/python3:pythoncontainer",
        "@exaudfclient_base//exa_udfclient_binary_common:exa_udfclient_binary_common_lib",
        "@protobuf//:protobuf",
        "@zmq//:zmq",
    ],
    defines = VM_ENABLED_DEFINES,
    data = ["@exaudfclient_base//:libexaudflib_complete.so"],
)

sh_library(
    name = "wrapper_generator_bin",
    srcs = select({
        "@exaudfclient_base//:valgrind_wrapper": ["@exaudfclient_base//:create_binary_wrapper_valgrind.sh"],
        "@exaudfclient_base//:valgrind_massif_wrapper": ["@exaudfclient_base//:create_binary_wrapper_valgrind_massif.sh"],
        "@exaudfclient_base//:stdout_to_bucketfs": ["@exaudfclient_base//:create_binary_wrapper_stdout_to_bucketfs.sh"],
        "//conditions:default": ["@exaudfclient_base//:create_binary_wrapper.sh"],
    }),
)

SLOW_WRAPPER_BINARY = """$(location :wrapper_generator_bin) "$(location :exaudfclient_bin)" "$@" "$(location :exaudfclient.template.sh)" """
FAST_BINARY = """cp "$(location :exaudfclient_bin)" "$@" """
CREATE_BINARY_SCRIPT = select({
    "@exaudfclient_base//:fast_binary": FAST_BINARY,
    "@exaudfclient_base//:slow_wrapper": SLOW_WRAPPER_BINARY,
    "//conditions:default": FAST_BINARY,
})

genrule(
    name = "exaudfclient",
    cmd = CREATE_BINARY_SCRIPT,
    outs = ["exaudfclient"],
    srcs = [
        ":exaudfclient_bin",
        ":exaudfclient.template.sh",
        ":wrapper_generator_bin",
        "@exaudfclient_base//:libexaudflib_complete.so",
    ],
    output_to_bindir = True,
)

SLOW_WRAPPER_STATIC_BINARY = """$(location :wrapper_generator_bin) "$(location :exaudfclient_static_bin)" "$@" "$(location :exaudfclient.template.sh)" """
FAST_BINARY_STATIC = """cp "$(location :exaudfclient_static_bin)" "$@" """
CREATE_STATIC_BINARY_SCRIPT = select({
    "@exaudfclient_base//:fast_binary": FAST_BINARY_STATIC,
    "@exaudfclient_base//:slow_wrapper": SLOW_WRAPPER_STATIC_BINARY,
    "//conditions:default": FAST_BINARY_STATIC,
})

genrule(
    name = "exaudfclient_static",
    cmd = CREATE_STATIC_BINARY_SCRIPT,
    outs = ["exaudfclient_static"],
    srcs = [
        ":exaudfclient_static_bin",
        ":exaudfclient.template.sh",
        ":wrapper_generator_bin",
        "@exaudfclient_base//:libexaudflib_complete.so",
    ],
    output_to_bindir = True,
)
