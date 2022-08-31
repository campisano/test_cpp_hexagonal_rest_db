ARG FROM_IMAGE
FROM --platform=linux/amd64 $FROM_IMAGE AS linux-amd64

ARG BUILD_DIR_AMD64

RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get -qq -y update \
    && apt-get -qq -y install apt-utils > /dev/null \
    && apt-get -qq -y install libspdlog1 > /dev/null \
    && apt-get -qq -y install libyaml-cpp0.6 > /dev/null \
    && apt-get -qq -y install libpqxx-6.4 > /dev/null \
    && apt-get -qq clean \
    && rm -rf /var/lib/apt/lists/* /var/cache/apt/* /usr/share/man/*

RUN useradd -r -U app -d /srv/app -m

WORKDIR /srv/app

COPY ./resources ./resources
COPY ./$BUILD_DIR_AMD64/build/ ./
COPY ./$BUILD_DIR_AMD64/src/domain/build ./src/domain/build
COPY ./$BUILD_DIR_AMD64/src/application/build ./src/application/build
COPY ./$BUILD_DIR_AMD64/src/adapters/build ./src/adapters/build

RUN find . -type d -exec chmod 0755 {} \;
RUN find /srv/app -type f -exec chmod a+r {} \;





ARG FROM_IMAGE
FROM --platform=linux/arm64/v8 $FROM_IMAGE AS linux-arm64

ARG BUILD_DIR_ARM64V8

RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get -qq -y update \
    && apt-get -qq -y install apt-utils > /dev/null \
    && apt-get -qq -y install libspdlog1 > /dev/null \
    && apt-get -qq -y install libyaml-cpp0.6 > /dev/null \
    && apt-get -qq -y install libpqxx-6.4 > /dev/null \
    && apt-get -qq clean \
    && rm -rf /var/lib/apt/lists/* /var/cache/apt/* /usr/share/man/*

RUN useradd -r -U app -d /srv/app -m

WORKDIR /srv/app

COPY ./resources ./resources
COPY ./$BUILD_DIR_ARM64V8/build/ ./
COPY ./$BUILD_DIR_ARM64V8/src/domain/build ./src/domain/build
COPY ./$BUILD_DIR_ARM64V8/src/application/build ./src/application/build
COPY ./$BUILD_DIR_ARM64V8/src/adapters/build ./src/adapters/build

RUN find . -type d -exec chmod 0755 {} \;
RUN find /srv/app -type f -exec chmod a+r {} \;





ARG TARGETOS
ARG TARGETARCH
FROM ${TARGETOS}-${TARGETARCH} as final

USER app:app
ENV LD_LIBRARY_PATH=src/domain/build/lib:src/application/build/lib:src/adapters/build/lib
CMD ["./bin/example"]
