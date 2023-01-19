rm -rf build

(
mkdir -p build
cd build
mkdir -p static
)

# build static
g++ -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux src/main/c/MapboxNativeBridge.cpp -o build/static/MapboxNativeBridge.o

# build shared libs
g++ -shared -fPIC -o build/libmapbox-kaffa.so build/static/MapboxNativeBridge.o -lc
