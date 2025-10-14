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
emmake make

# Flag for a release build
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release
```

``` bash
#To view html:
python3 -m http.server 8080
```