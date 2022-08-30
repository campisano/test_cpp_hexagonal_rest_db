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
apt-get -qq -y install g++ make cmake > /dev/null
apt-get -qq -y install libspdlog1 libspdlog-dev > /dev/null
apt-get -qq -y install libyaml-cpp0.6 libyaml-cpp-dev > /dev/null
apt-get -qq -y install libpqxx-6.4 libpqxx-dev > /dev/null
apt-get -qq -y install libcpputest-dev > /dev/null
apt-get -qq -y install wget unzip > /dev/null

mv -n /var/cache/apt/* ${CACHE_DIR}/var/cache/apt/

wget -P ${CACHE_DIR}/sonar/pkg -c -nv --no-check-certificate https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
mkdir -p ${CACHE_DIR}/sonar/wrapper
unzip -d ${CACHE_DIR}/sonar/wrapper -q -n ${CACHE_DIR}/sonar/pkg/build-wrapper-linux-x86.zip



cp -a ${BUILD_DIR}/* .
make -e clean
${CACHE_DIR}/sonar/wrapper/build-wrapper-linux-x86/build-wrapper-linux-x86-64 --out-dir .bw-output make -e debug
make -e test
make -e gcov



SONARSCAN_VER="4.7.0.2747"
SONARSCAN_URL="https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-${SONARSCAN_VER}-linux.zip"
mkdir -p ${CACHE_DIR}/sonar/pkg
wget -P ${CACHE_DIR}/sonar/pkg -c -nv --no-check-certificate "${SONARSCAN_URL}"
mkdir -p ${CACHE_DIR}/sonar/scanner
unzip -d ${CACHE_DIR}/sonar/scanner -q -n "${CACHE_DIR}/sonar/pkg/sonar-scanner-cli-${SONARSCAN_VER}-linux.zip"

mkdir -p ${CACHE_DIR}/sonar/home
export SONAR_USER_HOME=${CACHE_DIR}/sonar/home
${CACHE_DIR}/sonar/scanner/sonar-scanner-${SONARSCAN_VER}-linux/bin/sonar-scanner \
    -Dsonar.host.url=https://sonarcloud.io \
    -Dsonar.organization=${SONAR_ORGANIZATION} \
    -Dsonar.projectKey=${SONAR_PROJECT} \
    -Dsonar.scm.provider=git \
    -Dsonar.working.directory=.scannerwork \
    -Dsonar.sources=src \
    -Dsonar.sourceEncoding=UTF-8 \
    -Dsonar.coverage.exclusions=**/test/** \
    -Dsonar.cfamily.threads=1 \
    -Dsonar.cfamily.gcov.reportsPath=. \
    -Dsonar.cfamily.build-wrapper-output=.bw-output \
    -Dsonar.cfamily.cache.enabled=false
