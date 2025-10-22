```bash
#Emscripten:
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
```

build for emscripten
```bash
emcmake cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -s USE_FREETYPE=1 -s USE_HARFBUZZ=1

```


``` bash
#To view html from build/release/:
python3 -m http.server 8080
```