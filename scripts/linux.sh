#!/bin/bash

# Navigate to project root
cd "$(dirname "$0")/.."

echo "================================"
echo "Building spiral-flap..."
echo "================================"
echo ""

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Configure CMake
echo "Configuring CMake..."
if ! cmake ..; then
    echo ""
    echo "❌ ERROR: CMake configuration failed! [Don't Worry Aamir and Fatima i believe in you both :D]"
    echo "Check the error messages above for details."
    exit 1
fi

echo ""

# Build the project
echo "Building project..."
if ! cmake --build .; then
    echo ""
    echo "❌ ERROR: Build failed! [it's no big deal you can figure it out I believe in you both Aamir and Fatima]"
    echo "Check the compilation errors above."
    exit 1
fi

echo ""
echo "================================"
echo "✅ Build successful!"
echo "Executable location: bin/spiral-flap"
echo "================================"
echo ""
echo "Run with: ./bin/spiral-flap"
