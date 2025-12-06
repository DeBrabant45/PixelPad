#!/bin/bash
set -e

# Ensure system dependencies are installed
echo "Installing system dependencies..."
sudo apt update
sudo apt install -y build-essential autoconf automake autoconf-archive \
    libltdl-dev libsystemd-dev libcap-dev libblkid-dev libmount-dev \
    libpam0g-dev libselinux1-dev uuid-dev gperf zlib1g-dev liblz4-dev \
    liblzma-dev libzstd-dev meson ninja-build pkg-config python3-dev \
    python3-pip python3-setuptools python3-wheel

# Ensure Python dependencies are installed
echo "Installing Python dependencies..."
python3 -m pip install --user --upgrade pip
python3 -m pip install --user jinja2

# Clone vcpkg if it doesn't exist
if [ ! -d "vcpkg" ]; then
    echo "Cloning vcpkg..."
    git clone https://github.com/microsoft/vcpkg.git
else
    echo "vcpkg already cloned"
fi

# Bootstrap vcpkg if the executable doesn't exist
if [ ! -f "vcpkg/vcpkg" ]; then
    echo "Bootstrapping vcpkg..."
    (cd vcpkg && ./bootstrap-vcpkg.sh)
else
    echo "vcpkg already bootstrapped"
fi

# Force vcpkg to use system libraries instead of building libsystemd/libcap

# Install dependencies using manifest (vcpkg.json)
echo "Installing vcpkg dependencies..."
./vcpkg/vcpkg install

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
else
    echo "Build directory already exists"
fi

echo "Setup complete!"
