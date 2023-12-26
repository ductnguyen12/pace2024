mkdir -p build
cd build
cmake ..
cmake --build .
if [ "$1" == "-c" ]; then
    mv mincrossing ../mincrossing
fi
cd ..