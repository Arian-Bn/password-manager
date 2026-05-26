FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    qt6-base-dev \
    qt6-base-dev-tools \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libsqlite3-dev \
    libgtest-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN git submodule update --init --recursive

RUN rm -rf build

RUN cmake -B build -DCMAKE_CXX_STANDARD=20
RUN cmake --build build

CMD ["./build/notes_manager"]
