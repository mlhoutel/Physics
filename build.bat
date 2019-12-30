@echo off
color 0a

:menu
cls
echo [1] Compile debug
echo [2] Compile and run debug 
echo [3] Run debug 
echo [4] Compile release 
echo [5] Compile and run release
echo [6] Run release
echo [7] Exit
set /p user=

if %user% == 1 goto cDebug
if %user% == 2 goto crDebug
if %user% == 3 goto rDebug
if %user% == 4 goto cRelease
if %user% == 5 goto crRelease
if %user% == 6 goto rRelease
if %user% == 7 exit

:cDebug
cls
echo Compiling for debug...
g++ -o bin/debug/*.o -c source/*.cpp -std=c++14 -Werror -Wfatal-errors -DSFML_STATIC -I D:\Librairies\C\SFML-2.5.1-Static\SFML\include
g++ bin/debug/*.o -o bin/debug/Debug.exe -L D:\Librairies\C\SFML-2.5.1-Static\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
echo Done && pause >nul
goto menu

:crDebug
cls
echo Compiling for debug...
g++ -o bin/debug/*.o -c source/*.cpp -std=c++14 -Werror -Wfatal-errors -DSFML_STATIC -I D:\Librairies\C\SFML-2.5.1-Static\SFML\include
g++ bin/debug/*.o -o bin/debug/Debug.exe -L D:\Librairies\C\SFML-2.5.1-Static\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
echo Done
"bin/debug/Debug.exe"
goto menu

:rDebug
cls
"bin/debug/Debug.exe"
goto menu

:cRelease
cls
echo Compiling for release...
g++ -o bin/release/*.o -c source/*.cpp -std=c++14 -Werror -Wfatal-errors -DSFML_STATIC -I D:\Librairies\C\SFML-2.5.1-Static\SFML\include -O3 -s -fexpensive-optimizations
g++ bin/release/*.o -o bin/release/Release.exe -L D:\Librairies\C\SFML-2.5.1-Static\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
echo Done && pause >nul
goto menu

:crRelease
cls
echo Compiling for release...
g++ -o bin/release/*.o -c source/*.cpp -std=c++14 -Werror -Wfatal-errors -DSFML_STATIC -I D:\Librairies\C\SFML-2.5.1-Static\SFML\include -O3 -s -fexpensive-optimizations
g++ bin/release/*.o -o bin/release/Release.exe -L D:\Librairies\C\SFML-2.5.1-Static\SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
echo Done
"bin/release/Release.exe"
goto menu

:rRelease
cls
"bin/release/Release.exe"
goto menu