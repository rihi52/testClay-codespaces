```bash
#Emscripten:
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
```

build
```bash
mkdir -p build && cd build
emcmake cmake ..
emmake make

# Flag for a release build
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release

# Maybe without cmake??
emcc -sUSE_SDL=3 -lSDL3_TTF ../src/global.c ../src/main_window.c ../src/main.c ../src/styles.c -o hello.html
```

build for emscripten
```bash
emcmake cmake -S . -B build
cd build
# Just use this one from build/ if you don't need to rebuild
emmake make

#Use this one now, it builds but the html doesn't open correctly
emcmake cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -s USE_FREETYPE=1 -s USE_HARFBUZZ=1

```

build for OS
```bash
cmake -S . -B build_os
cmake --build build_os
```

``` bash
#To view html from build/release/:
python3 -m http.server 8080
```