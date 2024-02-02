mkdir -p build
cd build

debug_flag=0
generate_flag=0
gurubi_lib="/opt/gurobi1100/linux64/"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -d)
            debug_flag=1
            ;;
        -g)
            generate_flag=1
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
    cmake -DGUROBI_DIR=$gurubi_lib -DCMAKE_BUILD_TYPE=DebugMode ..
elif [ "$generate_flag" == "1" ]; then
    echo "GENERATE MODE enabled"
    cmake -DCMAKE_BUILD_TYPE=GenerateMode ..
else
    echo "DEBUG MODE disabled"
    cmake -DGUROBI_DIR=$gurubi_lib -DCMAKE_BUILD_TYPE=Release ..
fi

cmake --build .
cd ..