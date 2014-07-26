CC = g++
CPPFLAGS = -std=c++0x -O3 #-Wall#-fprofile-arcs -ftest-coverage -O0
LIBS =
INCLUDES =
TARGET = HW4

SRC = $(wildcard *.cc)
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

light.o: light.h vertex.h face.h elipse.h MatMath.h
vertex.o: vertex.h MatMath.h
camera.o: camera.h wireframe.h light.h vertex.h face.h elipse.h material.h
camera.o: group.h MatMath.h
MatMath.o: MatMath.h
material.o: material.h light.h vertex.h face.h elipse.h MatMath.h
group.o: group.h vertex.h face.h elipse.h
elipse.o: elipse.h vertex.h MatMath.h
wireframe.o: wireframe.h
face.o: face.h vertex.h MatMath.h
reader.o: reader.h group.h vertex.h face.h elipse.h light.h material.h
reader.o: camera.h wireframe.h
