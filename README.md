# Docker Fun (Qt)

A simple Qt6 desktop application used to learn and experiment with running native C++ GUI applications inside Docker containers.

This project serves as a sandbox for learning:

* Docker and Docker Compose
* Multi-stage Docker builds
* Qt6 Widgets
* CMake and Ninja
* C++17
* GUI forwarding from containers (X11/Wayland)
* Cross-platform development workflows

---

## Features

* Qt6 Widgets application
* CMake-based build system
* Dockerized development environment
* Docker Compose support
* Modern C++17

---

## Project Structure

```text
Docker_Fun/
├── CMakeLists.txt
├── Dockerfile
├── docker-compose.yml
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
└── README.md
```

---

## Requirements

### Native Development

* CMake 3.16+
* Qt6
* C++17 compiler
* Ninja (recommended)

### Docker

* Docker Engine
* Docker Compose

If running the GUI from a container, an X11 or Wayland display server is also required.

---

## Building Natively

```bash
cmake -B build -G Ninja
cmake --build build
./build/Docker_Fun_QT
```

---

## Building with Docker

Build the image:

```bash
docker compose build
```

Run the application:

```bash
docker compose up
```

or rebuild automatically:

```bash
docker compose up --build
```

---

## Running the GUI

When using X11, allow Docker to access your display:

```bash
xhost +local:docker
```

The application will use your host display through the X11 socket.

> **Note:** Docker Desktop on Linux may require additional configuration for GUI applications. Native Docker Engine is recommended for the best experience.

---

## Technologies

* C++17
* Qt6 Widgets
* CMake
* Ninja
* Docker
* Docker Compose
* Arch Linux (development platform)

---

## Purpose

This repository exists primarily as a learning project for containerized desktop application development. It explores how modern C++ applications can be built, packaged, and executed inside Docker while still presenting a native graphical user interface.

As the project grows, it may expand to include additional demonstrations of Docker networking, persistent storage, databases, and other container technologies alongside Qt desktop development.

---

## License

This project is released under the MIT License unless otherwise specified.
