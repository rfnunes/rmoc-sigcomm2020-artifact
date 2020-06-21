CC := g++
CCFLAGS := -std=c++17
INC := -I Includes

SRC0 = $(wildcard Sources/Main/*.cpp)
SRC1 = $(wildcard Sources/DominantPathsProtocols/NonRestartingProtocol/*.cpp)
SRC2 = $(wildcard Sources/DataStructures/*.cpp)
SRC3 = $(wildcard Sources/Graph/*.cpp)
SRC4 = $(wildcard Sources/DominantPathsProtocols/RestartingProtocol/*.cpp)

OBJ0 = $(addprefix Binaries/,$(notdir $(SRC3:.cpp=.o)))

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o )

Executables/StableStateNonRestartingProtocol.exe: Binaries/StableStateNonRestartingProtocol.o Binaries/NonRestartingProtocolCode.o Binaries/NonRestartingRoutingSimulator.o Binaries/NonRestartingRoutingState.o Binaries/AugmentedPriorityQueue.o Binaries/PriorityQueue.o Binaries/Graph.o
	$(CC) -o Executables/StableStateNonRestartingProtocol.exe Binaries/StableStateNonRestartingProtocol.o Binaries/NonRestartingProtocolCode.o Binaries/NonRestartingRoutingSimulator.o Binaries/NonRestartingRoutingState.o Binaries/AugmentedPriorityQueue.o Binaries/PriorityQueue.o Binaries/Graph.o

Binaries/%.o: $(SRC1) $(SRC0) $(SRC2) $(SRC3)
	$(CC) -c -Wall $(INC) $(CCFLAGS) -o $@ $<

clean:
	rm -fv Binaries/*.o Executables/*.exe

test:
	@echo $(SRC0)

# Binaries/StableStateNonRestartingProtocol.o: Sources/Main/StableStateNonRestartingProtocol.cpp
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) Sources/Main/StableStateNonRestartingProtocol.cpp -o Binaries/StableStateNonRestartingProtocol.o

# Binaries/NonRestartingProtocolCode.o: Sources/DominantPathsProtocols/NonRestartingProtocol/NonRestartingProtocolCode.cpp
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) Sources/DominantPathsProtocols/NonRestartingProtocol/NonRestartingProtocolCode.cpp -o Binaries/NonRestartingProtocolCode.o

# Binaries/NonRestartingRoutingSimulator.o: Sources/DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingSimulator.cpp
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) Sources/DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingSimulator.cpp -o Binaries/NonRestartingRoutingSimulator.o

# Binaries/NonRestartingRoutingState.o: Sources/DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingState.cpp
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) Sources/DominantPathsProtocols/NonRestartingProtocol/NonRestartingRoutingState.cpp -o Binaries/NonRestartingRoutingState.o

# Binaries/AugmentedPriorityQueue.o: Sources/DataStructures/AugmentedPriorityQueue.cpp
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) Sources/DataStructures/AugmentedPriorityQueue.cpp -o Binaries/AugmentedPriorityQueue.o

# Binaries/PriorityQueue.o: Sources/DataStructures/PriorityQueue.cpp
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) Sources/DataStructures/PriorityQueue.cpp -o Binaries/PriorityQueue.o

# Binaries/Graph.o: $(SRC3)
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) -o $@ $<

# Binaries/AugmentedPriorityQueue.o: $(SRC2)
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) -o $@ $<

# Binaries/PriorityQueue.o: $(SRC2)
# 	$(CC) -c -Wall $(INC) $(CCFLAGS) -o $@ $<
