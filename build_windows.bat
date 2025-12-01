@echo off
setlocal enabledelayedexpansion

REM Criar diretório bin se não existir
if not exist bin (
    mkdir bin
)

REM Criar diretório .obj se não existir
if not exist .obj (
    mkdir .obj
)

REM Compilar todos os arquivos .cpp em src
for %%f in (src\*.cpp) do (
    if exist "%%f" (
        set "filename=%%~nf"
        g++ -Iinc -Isrc -c "%%f" -o ".obj/!filename!.o"
    )
)

REM Lincar os objetos
g++ .obj\*.o -o bin\main.exe

echo Build process complete! Available at bin\main.exe
