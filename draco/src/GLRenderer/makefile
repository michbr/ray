CC =g++
CPPFLAGS =-std=c++0x -O3#-Wall#-fprofile-arcs -ftest-coverage -O0
LIBS =-lGL -lX11 -lGLU
WINLIBS =-lopengl32 -lgdi32
INCLUDES =
TARGET = LOOK
PROJECTDIR = /home/brian/Desktop/gondor/newGraph/again

SRC = $(wildcard *.cc *.cpp)
OBJS = $(patsubst %.cc,%.o,$(SRC))
WINOBJS = $(patsubst %.o,%-win.o,$(OBJS))

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.PHONY : clean depend
.PHONY : lines depend
.PHONY : update depend

depend:		makefile $(SRC)
	cp -pr . /tmp/proj/; cd /tmp/proj; makedepend $(INCLUDES) $(SRC); cp /tmp/proj/makefile $(PROJECTDIR)
	echo $(SRC) | sed -r 's/(\S+)(\.\S+)\s*/$(CC) $(CPPFLAGS) -c -o \1-win.o \1\2\r\n/g' > compile.bat
	echo $(CC) $(CPPFLAGS) -o $(TARGET)32 $(WINOBJS) $(WINLIBS)  >> compile.bat
	echo "\r\npause" >> compile.bat

lines:
	cat $(SRC)  | wc -l

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(WINOBJS) $(TARGET)32.exe
# DO NOT DELETE

camera.o: camera.h dragonmath.h /usr/include/GL/gl.h /usr/include/GL/glext.h
camera.o: /usr/include/inttypes.h /usr/include/features.h
camera.o: /usr/include/stdc-predef.h /usr/include/stdint.h
controls.o: controls.h camera.h dragonmath.h /usr/include/GL/gl.h
controls.o: /usr/include/GL/glext.h /usr/include/inttypes.h
controls.o: /usr/include/features.h /usr/include/stdc-predef.h
controls.o: /usr/include/stdint.h dragon.h window.h renderer.h
dragon.o: dragon.h camera.h dragonmath.h window.h renderer.h
dragon.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
dragon.o: /usr/include/inttypes.h /usr/include/features.h
dragon.o: /usr/include/stdc-predef.h /usr/include/stdint.h controls.h
dragonmath.o: dragonmath.h /usr/include/GL/gl.h /usr/include/GL/glext.h
dragonmath.o: /usr/include/inttypes.h /usr/include/features.h
dragonmath.o: /usr/include/stdc-predef.h /usr/include/stdint.h
main.o: dragon.h camera.h dragonmath.h window.h renderer.h
main.o: /usr/include/GL/gl.h /usr/include/GL/glext.h /usr/include/inttypes.h
main.o: /usr/include/features.h /usr/include/stdc-predef.h
main.o: /usr/include/stdint.h
renderer.o: renderer.h window.h camera.h dragonmath.h /usr/include/GL/gl.h
renderer.o: /usr/include/GL/glext.h /usr/include/inttypes.h
renderer.o: /usr/include/features.h /usr/include/stdc-predef.h
renderer.o: /usr/include/stdint.h /usr/include/GL/glu.h
window.o: window.h
