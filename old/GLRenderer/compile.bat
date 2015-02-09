g++ -std=c++0x -O3 -c -o camera-win.o camera.cc
g++ -std=c++0x -O3 -c -o controls-win.o controls.cc
g++ -std=c++0x -O3 -c -o dragon-win.o dragon.cc
g++ -std=c++0x -O3 -c -o dragonmath-win.o dragonmath.cc
g++ -std=c++0x -O3 -c -o main-win.o main.cc
g++ -std=c++0x -O3 -c -o renderer-win.o renderer.cc
g++ -std=c++0x -O3 -c -o window-win.o window.cc
g++ -std=c++0x -O3 -c -o winMain-win.o winMain.cc

g++ -std=c++0x -O3 -o LOOK32 camera-win.o controls-win.o dragon-win.o dragonmath-win.o main-win.o renderer-win.o window-win.o winMain-win.o -lopengl32 -lgdi32

pause
