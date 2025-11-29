#!/usr/bin/env bash

if [ ! -d bin ]; then
    mkdir -p bin
fi

if [ ! -d .obj ]; then
    mkdir -p .obj
fi

g++ -Iinc -Isrc -c src/main.cpp -o .obj/main.o
g++ .obj/*.o -o bin/main

echo Build process complete! Available at bin/
