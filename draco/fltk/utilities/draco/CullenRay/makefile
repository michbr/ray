

# 
# Cullen Eason
# semimono
# Assignment 3: Global Ray Casting Spheres
# 10/21/14
# CS 410
# Ross Beveridge
# 

objectFiles=
sourceFiles=material.cc math.cc shape.cc sphere.cc world.cc camera.cc lightSource.cc mesh.cc image.cc 
mainFile=HW5.cc
executable=HW5

CXXFLAGS= -std=c++11 -Wfatal-errors -Wall -Wextra -pedantic -O3 -mssse3 -mfpmath=sse -flto


all: $(sourceFiles) $(mainFile)
	g++ $(CXXFLAGS) $(sourceFiles) $(mainFile) -o $(executable)


target:
	tar -cvf HW5.tar *.h *.cc

clean:
	rm -f $(executable) $(objectFiles)
