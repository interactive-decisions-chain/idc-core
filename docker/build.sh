#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-idcccore/idcc}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/idccd docker/bin/
cp $BUILD_DIR/src/idcc-cli docker/bin/
cp $BUILD_DIR/src/idcc-tx docker/bin/
strip docker/bin/idccd
strip docker/bin/idcc-cli
strip docker/bin/idcc-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
