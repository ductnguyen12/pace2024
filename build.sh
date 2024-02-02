mkdir -p build
cd build

debug_flag=0
generate_flag=0
bary_flag=0
medium_flag=0
jump_flag=0
gurubi_lib="/opt/gurobi1100/linux64/"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -d)
            debug_flag=1
            ;;
        -g)
            generate_flag=1
            ;;
        -b)
            bary_flag=1
            ;;
        -m)
            medium_flag=1
            ;;
        -j)
            jump_flag=1
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
elif [ "$bary_flag" == "1" ]; then
    echo "BARY MODE enabled"
    cmake -DGUROBI_DIR=$gurubi_lib -DCMAKE_BUILD_TYPE=BaryMode ..
elif [ "$jump_flag" == "1" ]; then
    echo "JUMP MODE enabled"
    cmake -DGUROBI_DIR=$gurubi_lib -DCMAKE_BUILD_TYPE=JumpMode ..
elif [ "$medium_flag" == "1" ]; then
    echo "MEDIUM MODE enabled"
    cmake -DGUROBI_DIR=$gurubi_lib -DCMAKE_BUILD_TYPE=MediumMode ..
else
    echo "RANDOM MODE disabled"
    cmake -DGUROBI_DIR=$gurubi_lib -DCMAKE_BUILD_TYPE=RandomMode ..
fi

cmake --build .
cd ..