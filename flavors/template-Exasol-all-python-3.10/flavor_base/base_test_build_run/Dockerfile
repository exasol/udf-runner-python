FROM {{language_deps}}

ARG UDF_RUNNER_CPP_COMMIT=b3a8c204a2555b373c66110d5e8301a374b32a6a

RUN mkdir /conf /buckets

COPY --from={{base_test_deps}} /usr /usr
RUN true # workaround for https://github.com/moby/moby/issues/37965

COPY --from={{base_test_deps}} /lib /lib
RUN true # workaround for https://github.com/moby/moby/issues/37965

COPY --from={{base_test_deps}} /bin /bin
RUN true # workaround for https://github.com/moby/moby/issues/37965

COPY --from={{base_test_deps}} /opt /opt
RUN true # workaround for https://github.com/moby/moby/issues/37965

COPY --from={{base_test_deps}} /etc /etc
RUN true # workaround for https://github.com/moby/moby/issues/37965

COPY --from={{base_test_deps}} /build_info /build_info
RUN true # workaround for https://github.com/moby/moby/issues/37965

RUN exaslpm export-variables --out-file /env

RUN ldconfig

RUN mkdir /exaudfclient /exaudf
COPY /exaudfclient/ /exaudfclient/

WORKDIR /exaudfclient/
RUN ["/bin/bash", "-c", "source /env && bash build.sh --config no-tty -c dbg --config python --config test-binaries"]
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
