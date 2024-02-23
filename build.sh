mkdir -p build
cd build

generate_flag=0
bary_flag=0
median_flag=0
jump_flag=0
no_ilp_flag=0
gurubi_lib="/opt/gurobi1100/linux64/"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -g)
            generate_flag=1
            ;;
        -b)
            bary_flag=1
            ;;
        -m)
            median_flag=1
            ;;
        -j)
            jump_flag=1
            ;;
        -x)
            no_ilp_flag=1
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
    shift
done

build_command="cmake -DGUROBI_DIR=$gurubi_lib"
if [ "$generate_flag" == "1" ]; then
    echo "GENERATE MODE enabled"
    build_command+=" -DGENERATE_MODE=ON"
    # cmake -DCMAKE_BUILD_TYPE=GenerateMode ..
fi
if [ "$bary_flag" == "1" ]; then
    echo "BARY MODE enabled"
    build_command+=" -DBARY_MODE=ON"
    # cmake -DCMAKE_BUILD_TYPE=BaryMode ..
elif [ "$median_flag" == "1" ]; then
    echo "MEDIAN MODE enabled"
    build_command+=" -DMEDIAN_MODE=ON"
    # cmake -DCMAKE_BUILD_TYPE=MediumMode ..
else
    echo "RANDOM MODE enabled"
    build_command+=" -DRANDOM_MODE=ON"
    # cmake -DCMAKE_BUILD_TYPE=RandomMode ..
fi
if [ "$jump_flag" == "1" ]; then
    echo "JUMP MODE enabled"
    build_command+=" -DJUMP_MODE=ON"
    # cmake  -DCMAKE_BUILD_TYPE=JumpMode ..
fi
if [ "$no_ilp_flag" == "1" ]; then
    echo "NO ILP BUILT!"
    build_command+=" -DNO_ILP=ON"
else 
    echo "ILP Implemented"
    build_command+=" -DGUROBI_DIR=$gurubi_lib"
fi

build_command+=" .."

echo "Final build command: $build_command";

eval "$build_command";

cmake --build .
cd ..