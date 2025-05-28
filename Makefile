#dvirbto@gmail.com

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -IGUI -IRoles -ITest -IEx3
LDFLAGS =

# SFML flags
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Files and folders
GUI_SRC = GUI/mainWindow.cpp
ROLES_SRC = $(wildcard Roles/*.cpp)
TEST_SRC = Test/Tests.cpp
GAME_SRC = Game.cpp
DEMO_SRC = Demo.cpp

MAIN_OBJ = $(GUI_SRC:.cpp=.o)
ROLES_OBJ = $(ROLES_SRC:.cpp=.o)
GAME_OBJ = $(GAME_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
DEMO_OBJ = $(DEMO_SRC:.cpp=.o)

# Targets
all: Main

Main: $(MAIN_OBJ) $(ROLES_OBJ) $(GAME_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_FLAGS)

test: $(TEST_OBJ) $(ROLES_OBJ) $(GAME_OBJ)
	$(CXX) $(CXXFLAGS) -o Tests $^

valgrind: test
	valgrind --leak-check=full ./Tests

demo: $(DEMO_OBJ) $(ROLES_OBJ) $(GAME_OBJ)
	$(CXX) $(CXXFLAGS) -o Demo $^
	./Demo

clean:
	rm -f *.o GUI/*.o Roles/*.o Test/*.o Ex3/*.o Main Tests Demo
