CC=g++
CXXFLAGS=-Wall -std=c++11 -pthread

TARGET=arduino
SOURCES=board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp
HEADER=core_simulation.h mydevices.h
OBJECTS=./Objects/board.o ./Objects/core_simulation.o ./Objects/mydevices.o ./Objects/sketch_ino.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

./Objects/board.o: board.cpp $(HEADER)
	$(CC) $(CXXFLAGS) -o $@ -c $< 

./Objects/core_simulation.o: core_simulation.cpp core_simulation.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/mydevices.o: mydevices.cpp mydevices.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/sketch_ino.o: sketch_ino.cpp core_simulation.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *~ ./Objects/*.o

mrproper: clean
	rm -f arduino

