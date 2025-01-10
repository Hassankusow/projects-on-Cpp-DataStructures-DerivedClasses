CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
TARGET = output
OBJS = main_33.o poke.o tree.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main_33.o: main_33.cpp
	$(CXX) $(CXXFLAGS) -c main_33.cpp

poke.o: poke.cpp
	$(CXX) $(CXXFLAGS) -c poke.cpp

tree.o: tree.cpp
	$(CXX) $(CXXFLAGS) -c tree.cpp

clean:
	rm -f $(TARGET) $(OBJS)

