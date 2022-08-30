#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

CACHE_DIR=/srv/cache
BUILD_DIR=/srv/build

mkdir -p ${CACHE_DIR}/var/cache/apt
cp -aT ${CACHE_DIR}/var/cache/apt /var/cache/apt
rm -f /etc/apt/apt.conf.d/docker*

export DEBIAN_FRONTEND=noninteractive
apt-get -qq -y update
apt-get -qq -y install apt-utils > /dev/null
apt-get -qq -y install make > /dev/null
apt-get -qq -y install libspdlog1 > /dev/null
apt-get -qq -y install libyaml-cpp0.6 > /dev/null
apt-get -qq -y install libpqxx-6.4 > /dev/null

mv -n /var/cache/apt/* ${CACHE_DIR}/var/cache/apt/

cp -a ${BUILD_DIR}/* .

make -e test
