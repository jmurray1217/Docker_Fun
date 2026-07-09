FROM archlinux:latest

RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
        base-devel \
        cmake \
        ninja \
        gcc \
        qt6-base \
        qt6-serialport \
        fontconfig \
        noto-fonts \
        ttf-dejavu && \
    pacman -Scc --noconfirm

WORKDIR /app

COPY . .

RUN rm -rf build && \
    cmake -S . -B build -G Ninja && \
    cmake --build build
ENV DISPLAY=:0

CMD ["./build/Docker_Fun_QT"]