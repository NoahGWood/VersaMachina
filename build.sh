set -e
BUILD_DIR="build"

# Linux build
echo "==> Building for Linux..."
cmake -B build -G Ninja . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/versa
