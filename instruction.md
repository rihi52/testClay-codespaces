Emscripten:
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh

build
```bash
mkdir build && cd build
emcmake cmake ..
emcmake make
```