#!/usr/bin/env bash

set -o errexit -o nounset -o pipefail

VERSION=$(cat ./VERSION)

echo "${VERSION}"
