# pace2024
Graph and Network Algorithms Lab (Exercises)

# Building tutorial
Build the project using 
```bash
./build.sh [-c] [-d]
```
- -c: copy the executable to the root folder (otherwise you can find it in the **/build** directory)
- -d: enable the debug mode (sets the flag DEBUG_MODE)

# Executing tutorial
The project is not finished yet and can only be executed by using, for example,
```bash
./mincrossing -a <algorithm> -t <milli-seconds> -i <input file>
```
```bash
./mincrossing -a GA -t 1234 -f "examples/OCR/tree_6_10.gr"
```