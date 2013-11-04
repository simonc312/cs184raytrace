CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
LIBFLAGS=-lfreeimageplus
SOURCES=main.cpp Output.cpp Ray.cpp Scene.cpp Object.cpp Triangle.cpp Sphere.cpp Light.cpp PointLight.cpp DirectionalLight.cpp Attenuation.cpp Quality.cpp Transform.cpp Matrix4f.cpp Matrix3f.cpp Vertex3f.cpp Vector3f.cpp Color3f.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=as2
RM = /bin/rm -f

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	$(RM) *.o $(EXECUTABLE)
