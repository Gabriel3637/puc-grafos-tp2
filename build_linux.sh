#!/usr/bin/env bash

if [ ! -d bin ]; then
    mkdir -p bin
fi

if [ ! -d .obj ]; then
    mkdir -p .obj
fi

for file in src/*.cpp; do
    if [ -f "$file" ]; then
        filename=$(basename "$file" .cpp)

        g++ -std=c++23 -Iinc -Isrc -c "$file" -o ".obj/${filename}.o"
    fi
done

g++ -std=c++23 .obj/*.o -o bin/main

echo "Build process complete! Available at bin/main"
