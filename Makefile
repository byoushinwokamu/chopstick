CC = g++
CFLAGS = -std=c++17 -g

OBJ = game.o ManPlayer.o ComPlayer.o
TARGET = game 

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
