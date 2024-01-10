mkdir -p build
cd build

debug_flag=0
copy_flag=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        -d)
            debug_flag=1
            ;;
        -c)
            copy_flag=1
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
    shift
done

if [ "$debug_flag" == "1" ]; then
    echo "DEBUG MODE enabled"
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake ..
fi

cmake --build .
if [ "$copy_flag" == "1" ]; then
    mv mincrossing ../mincrossing
fi
cd ..