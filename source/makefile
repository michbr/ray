CC = g++
CPPFLAGS = -std=c++0x -O3 #-Wall#-fprofile-arcs -ftest-coverage -O0
LIBS =
INCLUDES =
TARGET = HW4

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

renderer.o: renderer.h vertex.h wireframe.h group.h face.h material.h
renderer.o: elipse.h light.h camera.h MatMath.h
MatMath.o: MatMath.h
light.o: light.h vertex.h face.h material.h elipse.h MatMath.h
vertex.o: vertex.h MatMath.h
group.o: group.h vertex.h face.h material.h elipse.h
parser.o: parser.h
camera.o: camera.h wireframe.h light.h vertex.h face.h material.h elipse.h
camera.o: group.h MatMath.h
material.o: material.h MatMath.h
elipse.o: elipse.h vertex.h material.h MatMath.h
wireframe.o: wireframe.h
face.o: face.h vertex.h material.h MatMath.h
reader.o: reader.h group.h vertex.h face.h material.h elipse.h light.h
reader.o: camera.h wireframe.h renderer.h materialparser.h parser.h
materialparser.o: materialparser.h parser.h material.h
