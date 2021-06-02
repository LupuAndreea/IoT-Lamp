CC = g++

LFLAGS  = -lpistache -ljsoncpp 
FSFLAGS = -ljsoncpp -lcurl
SFLAGS  = -ljsoncpp

SERVER_TARGET = serverWeb
FUSION_TARGET = fusion3
SOUND_TARGET  = sunet

all: build

build:
	$(CC) -o $(FUSION_TARGET) $(FUSION_TARGET).cpp $(FSFLAGS)
	$(CC) -o $(SERVER_TARGET) $(SERVER_TARGET).cpp $(LFLAGS)
	$(CC) -o $(SOUND_TARGET) $(SOUND_TARGET).cpp $(SFLAGS)
	xterm ./serverWeb& sleep 3
	xterm ./fusion3& sleep 3
	xterm ./sunet& sleep 3

clean:
	$(RM) $(SERVER_TARGET) $(FUSION_TARGET) $(SOUND_TARGET)
