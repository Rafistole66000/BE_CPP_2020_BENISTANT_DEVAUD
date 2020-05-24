CC=g++
CXXFLAGS=-Wall -std=c++11 -pthread -Wextra -Werror

TARGET=arduino
SOURCES=board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp board_manager.cpp ./Custom_Devices/pulse_sensor.cpp ./Custom_Devices/Wifi_module.cpp ./Custom_Devices/Bluetooth_module.cpp ./Custom_Devices/Bibliotheque.cpp
HEADER=core_simulation.h mydevices.h board_manager.h ./Custom_Devices/pulse_sensor.h ./Custom_Devices/Wifi_module.h ./Custom_Devices/Bluetooth_module.h ./Custom_Devices/Bibliotheque.h
OBJECTS=./Objects/board.o ./Objects/core_simulation.o ./Objects/mydevices.o ./Objects/board_manager.o ./Objects/sketch_ino.o ./Objects/pulse_sensor.o ./Objects/Wifi_module.o ./Objects/Bluetooth_module.o ./Objects/Bibliotheque.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

./Objects/board.o: board.cpp $(HEADER)
	$(CC) $(CXXFLAGS) -o $@ -c $< 

./Objects/core_simulation.o: core_simulation.cpp core_simulation.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/mydevices.o: mydevices.cpp mydevices.h ./Custom_Devices/pulse_sensor.h ./Custom_Devices/Wifi_module.h ./Custom_Devices/Bluetooth_module.h ./Custom_Devices/Bibliotheque.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/board_manager.o: board_manager.cpp board_manager.h core_simulation.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/pulse_sensor.o: ./Custom_Devices/pulse_sensor.cpp ./Custom_Devices/pulse_sensor.h
	$(CC) $(CXXFLAGS) -o $@ -c $<
	
./Objects/Wifi_module.o: ./Custom_Devices/Wifi_module.cpp ./Custom_Devices/Wifi_module.h
	$(CC) $(CXXFLAGS) -o $@ -c $<
	
./Objects/Bluetooth_module.o: ./Custom_Devices/Bluetooth_module.cpp ./Custom_Devices/Bluetooth_module.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/Bibliotheque.o: ./Custom_Devices/Bibliotheque.cpp ./Custom_Devices/Bibliotheque.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

./Objects/sketch_ino.o: sketch_ino.cpp core_simulation.h
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *~ ./Objects/*.o

mrproper: clean
	rm -f arduino

