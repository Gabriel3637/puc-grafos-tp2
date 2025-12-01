@echo off
REM Criar pastas se não existirem
if not exist "bin" mkdir "bin"
if not exist ".obj" mkdir ".obj"

REM Compilar cada arquivo .cpp na pasta src
for %%f in (src\*.cpp) do (
    REM Extrair apenas o nome do arquivo sem extensão
    set "filename=%%~nf"
    REM Compilar arquivo .cpp para .obj
    g++ -std=c++23 -Iinc -Isrc -c "%%f" -o ".obj\%%~nf.o"
)

REM Linkar todos os objetos para gerar o executável
g++ -std=c++23 .obj\*.o -o bin\main.exe

echo Build process complete! Available at bin\main.exe
