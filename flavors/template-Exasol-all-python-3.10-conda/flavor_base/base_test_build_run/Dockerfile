FROM {{base_test_deps}}

ARG UDF_RUNNER_CPP_COMMIT=b3a8c204a2555b373c66110d5e8301a374b32a6a

RUN mkdir /conf /buckets

RUN exaslpm export-variables --out-file /env

RUN ldconfig

RUN mkdir /exaudfclient /exaudf
COPY /exaudfclient/ /exaudfclient/

WORKDIR /exaudfclient/
# We need to build with optimize here, because the debug build fails to run with a runtime linking error regarding protobuf
RUN source /env && ./build.sh --config no-tty -c dbg --config python --config test-binaries --config fix_conda_ar_tool
RUN cp -r -L bazel-bin/* /exaudf

WORKDIR /exaudfclient/base
RUN ./test_udfclient.sh /exaudf/exaudfclient
RUN ./test_udfclient.sh /exaudf/exaudfclient_static

WORKDIR /
RUN mkdir /exasol_emulator
COPY emulator/ /exasol_emulator
RUN curl -fsSL "https://raw.githubusercontent.com/exasol/udf-runner-cpp/${UDF_RUNNER_CPP_COMMIT}/udf-runner-cpp/v1/base/exaudflib/zmqcontainer.proto" -o /exasol_emulator/zmqcontainer.proto \
    && printf '%s\n' '    optional exascript_ping ping = 9;' '    optional exascript_single_call_rep call = 10;' '}' >> /exasol_emulator/zmqcontainer.proto
RUN cd /exasol_emulator && protoc zmqcontainer.proto --python_out=.
