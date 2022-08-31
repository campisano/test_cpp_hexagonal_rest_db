#!/usr/bin/env bash

set -x -o errexit -o nounset -o pipefail

# vars
export DOCKER_IMAGE_FROM=$(./ci/custom/get_docker_image_run.sh)
export PROJECT_NAME=$(./ci/custom/get_project_name.sh)
export PROJECT_VERSION=$(./ci/custom/get_project_version.sh)
export RELEASE_TAG="${PROJECT_NAME}-${PROJECT_VERSION}"

# grant docker login
echo "${DOCKER_PASSWORD}" | docker login --username "${DOCKER_USERNAME}" --password-stdin

# push new tag, locking version and grant git write access
git config user.name "${GIT_USERNAME}"
git config user.email "${GIT_EMAIL}"
git remote set-url origin "https://${GIT_USERNAME}:${GIT_PASSWORD}@${GIT_REPOSITORY_URL}"
git tag ${RELEASE_TAG}
git push origin tag ${RELEASE_TAG}

docker pull "${DOCKER_REPOSITORY}:${RELEASE_TAG}" &> /dev/null && echo "ERROR: docker image \"${DOCKER_REPOSITORY}:${RELEASE_TAG}\" already exists" && exit 1

# build docker image
docker pull tonistiigi/binfmt:latest
docker run --privileged --rm tonistiigi/binfmt --uninstall qemu-*
docker run --privileged --rm tonistiigi/binfmt --install arm64
docker buildx ls
docker buildx create --use
docker buildx build --push --platform=linux/amd64,linux/arm64/v8  \
       --build-arg "BUILD_DIR_AMD64=${BUILD_DIR_AMD64=}" \
       --build-arg "BUILD_DIR_ARM64V8=${BUILD_DIR_ARM64V8=}" \
       --build-arg "FROM_IMAGE=${DOCKER_IMAGE_FROM=}" \
       --tag "${DOCKER_REPOSITORY}:${RELEASE_TAG}" \
       --tag "${DOCKER_REPOSITORY}:${PROJECT_NAME}-latest" \
       --file ci/custom/Dockerfile .
