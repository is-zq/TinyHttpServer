src=$(wildcard ../src/*.cpp)
object=$(patsubst ../src/%.cpp,%.o,$(src))
target=server
CXX=g++
CPPFLAGS=-I../include
CXXFLAGS=-O2

all:$(target)
$(target):$(object)
	$(CXX) -o $@ $^
%.o:../src/%.cpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(CXXFLAGS)

.PHONY:clean
clean:
	-rm -f $(traget) $(object)
