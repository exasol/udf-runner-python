FROM {{flavor_base_deps}}

RUN mkdir -p /build_info/packages/flavor_customization
COPY flavor_customization_packages.yml /build_info/packages/flavor_customization_packages.yml
RUN exaslpm install --package-file /build_info/packages/flavor_customization_packages.yml --build-step flavor_customization
