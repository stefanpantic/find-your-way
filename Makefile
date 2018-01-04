CXX 		= g++
STANDARD	= -std=c++17
DEBUG 		= -g
INCLUDE 	= -I./include
CXXFLAGS 	= -Wall -Wextra $(STANDARD) $(INCLUDE) $(DEBUG)
LDFLAGS 	= -lGL -lGLU -lglut -lm
BIN			= build
MAIN		= main.cpp
MAINOBJ 	= $(BIN)/$(MAIN:.cpp=.o)
SRC 		= $(wildcard src/*.cpp)
HEAD 		= $(patsubst src/%.cpp, include/%.hpp, $(SRC))
HEADONLY 	= $(wildcard include/*.hpp include/opt/*.hpp)
OBJ 		= $(patsubst src/%.cpp, $(BIN)/%.o, $(SRC))
TARGET 		= $(BIN)/find-your-way

.PHONY: clean zip

all: $(BIN) $(TARGET)

$(TARGET): $(OBJ) $(MAINOBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(MAINOBJ): $(MAIN) $(HEADONLY)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

$(BIN)/%.o: src/%.cpp include/%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN):
	@test ! -d $@ && mkdir $@

clean:
	rm -rf $(BIN)
	rm -f ~*

zip:
	zip -r $(TARGET).zip ./
