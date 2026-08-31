FROM {{build_deps}}

RUN mkdir /exaudfclient /exaudf
COPY exaudfclient/ /exaudfclient/

RUN exaslpm export-variables --out-file /env

WORKDIR /exaudfclient/

RUN source /env && \
    export PROTOBUF_LIBRARY_PREFIX="${PROTOBUF_LIBRARY_PREFIX:-${MAMBA_ROOT_PREFIX:-/usr}/lib}" \
           PROTOBUF_INCLUDE_PREFIX="${PROTOBUF_INCLUDE_PREFIX:-${MAMBA_ROOT_PREFIX:-/usr}/include}" \
           ZMQ_LIBRARY_PREFIX="${ZMQ_LIBRARY_PREFIX:-${MAMBA_ROOT_PREFIX:-/usr}/lib}" \
           ZMQ_INCLUDE_PREFIX="${ZMQ_INCLUDE_PREFIX:-${MAMBA_ROOT_PREFIX:-/usr}/include}" && \
    ./build.sh --config no-tty --config optimize --config python --config slow-wrapper --config fix_conda_ar_tool
RUN cp -r -L bazel-bin/* /exaudf

WORKDIR /exaudfclient/base
RUN ./test_udfclient.sh /exaudf/exaudfclient

WORKDIR /exaudf

RUN rm -r /exaudfclient


RUN mkdir /conf /buckets
