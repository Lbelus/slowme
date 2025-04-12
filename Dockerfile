# Use the latest version of Ubuntu as the base image
FROM ubuntu:latest

# Set environment variables to non-interactive (this prevents some prompts)
ENV DEBIAN_FRONTEND=non-interactive

# Update package list and install essential packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    llvm\
    libssl-dev \
    clang \
    cmake \
    git \
    wget \
    unzip \
    pkg-config \
    nasm \
    python3 \             
    python3-pip \         
    python3-dev \     
    python3-venv

# Clean up to reduce image size
RUN   apt-get autoremove -y && \
      apt-get clean

# Reset environment variable
ENV DEBIAN_FRONTEND=

# Set the working directory
WORKDIR /workspace

# Set the default command
CMD ["bash"]
