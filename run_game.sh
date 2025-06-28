#!/bin/bash


set -e  

# 检查Docker是否安装
if ! command -v docker &> /dev/null; then
    echo "Docker未安装,请先安装Docker"
    exit 1
fi

# 检查Dockerfile是否存在
if [ ! -f "dockerfile" ]; then
    echo "找不到dockerfile文件"
    exit 1
fi


docker build -t qt-vcpkg-dev . || {
    echo "Docker镜像构建失败"
    exit 1
}

echo "Docker镜像构建成功"


CONTAINER_ID=$(docker run -d \
    -p 5900:5900 \
    -v $(pwd):/workspace \
    --name pvp-game-container \
    qt-vcpkg-dev \
    tail -f /dev/null)


docker exec $CONTAINER_ID bash -c "
    cd /workspace && \
    mkdir -p build && \
    cmake -B build -G"Ninja" && \
    cmake --build build
" || {
    echo "编译失败"
    docker rm -f $CONTAINER_ID
    exit 1
}

docker exec -it $CONTAINER_ID bash -c "
    cd /workspace && \
    QT_QPA_PLATFORM=vnc ./build/PvPFightingGame
" || {
    echo "游戏退出或出现错误"
}

docker rm -f $CONTAINER_ID
