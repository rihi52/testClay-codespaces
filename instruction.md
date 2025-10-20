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

``` bash
#To view html:
python3 -m http.server 8080
```