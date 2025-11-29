@echo off

if not exist bin mkdir bin

if not exist .obj mkdir .obj

g++ -Iinc -Isrc -c src/main.cpp -o .obj/main.o
g++ .obj/*.o -o bin/main.exe
