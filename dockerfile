FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && \
    apt-get install -y software-properties-common && \
    add-apt-repository -y universe && \
    apt-get update -y && \
    apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-multimedia-dev \
    qml6-module-* \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /workspace

CMD ["/bin/bash"]