.PHONY: all clean

CXX = g++
CXXFLAGS = -g -Wall -W -pedantic-errors -Wpedantic -Werror -std=c++11

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

OBJECTS = $(SOURCES:%.cpp=%.o)

default: hw7.out

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

hw7.out: $(OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
	@echo ""
	@echo "Building completed ..."
	@echo ""

clean:
	-@rm -f core
	-@rm -f hw7.out
	-@rm -f depend
	-@rm -f $(OBJECTS)

depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -MM *.cpp > $@

-include depend
