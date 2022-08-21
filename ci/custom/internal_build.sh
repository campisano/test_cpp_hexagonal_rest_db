#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

CACHE_DIR=/srv/cache
BUILD_DIR=/srv/build

mkdir -p ${CACHE_DIR}/var/cache/apt
cp -aT ${CACHE_DIR}/var/cache/apt /var/cache/apt
rm -f /etc/apt/apt.conf.d/docker*

export DEBIAN_FRONTEND=noninteractive
apt-get -qq -y update
apt-get -qq -y install --no-install-recommends apt-utils > /dev/null
apt-get -qq -y install --no-install-recommends libssl1.0.2 > /dev/null
apt-get -qq -y install --no-install-recommends gcc g++ make cmake libssl1.0-dev > /dev/null

mv -n /var/cache/apt/* ${CACHE_DIR}/var/cache/apt/



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
