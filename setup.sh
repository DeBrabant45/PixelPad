#!/bin/bash

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

# Install dependencies based on vcpkg.json
echo "Installing dependencies..."
./vcpkg/vcpkg install

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
else
    echo "Build directory already exists"
fi

echo "Setup complete!"
