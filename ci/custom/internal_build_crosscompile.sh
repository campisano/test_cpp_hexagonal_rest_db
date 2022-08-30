#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

CACHE_DIR=/srv/cache
BUILD_DIR=/srv/build

mkdir -p ${CACHE_DIR}/var/cache/apt
cp -aT ${CACHE_DIR}/var/cache/apt /var/cache/apt
rm -f /etc/apt/apt.conf.d/docker*

export DEBIAN_FRONTEND=noninteractive
dpkg --add-architecture arm64
apt-get -qq -y update
apt-get -qq -y install apt-utils > /dev/null
apt-get -qq -y install g++-aarch64-linux-gnu make cmake  > /dev/null
apt-get -qq -y install libspdlog1:arm64 libspdlog-dev:arm64 > /dev/null
apt-get -qq -y install libyaml-cpp0.6:arm64 libyaml-cpp-dev:arm64 > /dev/null
apt-get -qq -y install libpqxx-6.4:arm64 libpqxx-dev:arm64 > /dev/null
apt-get -qq -y install libcpputest-dev:arm64 > /dev/null

mv -n /var/cache/apt/* ${CACHE_DIR}/var/cache/apt/



export CXX=aarch64-linux-gnu-g++
export CC=aarch64-linux-gnu-gcc

cd lib
make -e
cd ..
cp -a ./lib ${BUILD_DIR}



make -e release

# copy build artifacts at them original positions to allow gcov to calculate test coverage
for I in ./ ./src/domain/ ./src/application ./src/adapters
do
    mkdir -p ${BUILD_DIR}/${I}
    cp -a ${I}/build ${BUILD_DIR}/${I}
done;
