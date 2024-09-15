CXX = g++
CFLAGS = -std=c++17 -g

OBJ = main.o ChopstickGame.o ManPlayer.o ComPlayer.o
TARGET = game 

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $(OBJ)

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
