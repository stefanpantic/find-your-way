CXX 		= g++
STANDARD	= -std=c++17
DEBUG 		= -g
INCLUDE 	= -I./include
CXXFLAGS 	= -Wall -Wextra $(STANDARD) $(INCLUDE) $(DEBUG)
LDFLAGS 	= -lGL -lGLU -lglut -lm
MAIN		= main.cpp
MAINOBJ 	= $(MAIN:.cpp=.o)
SRC 		= src/rgview.cpp \
			  src/rghub.cpp
HEAD 		= $(SRC:.cpp=.hpp)
HEADONLY 	= include/rgwindow.hpp \
			  include/rgdefines.hpp \
			  include/option.hpp \
			  include/opt/*.hpp
OBJ 		= $(SRC:.cpp=.o)
TARGET 		= find-your-way

.PHONY: clean zip

$(TARGET): $(OBJ) $(MAINOBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(MAINOBJ): $(MAIN) $(HEADONLY)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ) $(MAINOBJ)
	rm -f ~*
	rm -f $(TARGET)

zip:
	zip -r $(TARGET).zip ./
