CXX = g++ -std=c++11
CXXFLAGS = -Wall
OBJECTS = tands.o server.o client.o 

.PHONY: all

all: optimize

server.o: server.cpp  
	$(CXX) -c server.cpp -o server.o

client.o: client.cpp
	$(CXX) -c client.cpp -o client.o

tands.o: tands.c
	$(CXX) -c tands.c -o tands.o

assign3: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o server tands.o server.o 
	$(CXX) $(CXXFLAGS) -o client tands.o client.o

debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -g -o server tands.o server.o 
	$(CXX) $(CXXFLAGS) -g -o client tands.o client.o

optimize: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -O -o server tands.o server.o 
	$(CXX) $(CXXFLAGS) -O -o client tands.o client.o


# debug:  $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) -g -o prodcon $(OBJECTS)

# optimize: $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) -O -o prodcon $(OBJECTS)
# prodcon: prodcon.cpp tands.c
# 	g++ -Wall -pthread -std=c++11 -o prodcon tands.c prodcon.cpp 

clean:
	rm *.o server client