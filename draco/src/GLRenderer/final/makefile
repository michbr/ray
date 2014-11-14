CC = g++
CPPFLAGS = -std=c++0x -O3 #-Wall#-fprofile-arcs -ftest-coverage -O0
LIBS = -lGL -lglut -lGLU
INCLUDES =
TARGET = LOOK

SRC = $(wildcard *.cc *.cpp)
OBJS = $(patsubst %.cc,%.o,$(SRC))

#OBJS2 = $(patsubst %.cc,%.gcno,$(SRC))
	
$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

#$(TARGET).gcno: $(OBJS2) $(OBJS2)
#	$(CC) $(CPPFLAGS) $(OBJS) $(LIBS)

.PHONY : clean depend
.PHONY : lines depend
.PHONY : update depend

depend:		makefile $(SRC)
	makedepend $(INCLUDES) $(SRC)

lines:
	cat *.h *.cc | wc -l

clean:
	rm -f $(OBJS) $(TARGET)
# DO NOT DELETE

rwindow.o: /usr/include/stdlib.h /usr/include/features.h
rwindow.o: /usr/include/stdc-predef.h /usr/include/alloca.h
rwindow.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
rwindow.o: /usr/include/wchar.h /usr/include/xlocale.h /usr/include/GL/glew.h
rwindow.o: /usr/include/stdint.h /usr/include/GL/glu.h /usr/include/GL/gl.h
rwindow.o: /usr/include/GL/freeglut.h /usr/include/GL/freeglut_std.h
rwindow.o: /usr/include/GL/freeglut_ext.h rwindow.h
