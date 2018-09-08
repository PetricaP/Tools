SRC_PATH=src/
CC=g++
WN=-Wall -Wextra --pedantic -g -std=c++14
CFLAGS=-c ${WN}
INCL=-Iinclude/

VENDOR=src/vendor
EXE=cppgen

SRC=$(wildcard $(SRC_PATH)*.cpp)
OBJ=$(subst src, obj, $(SRC:.cpp=.o))

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	    $(CC) $(OBJ) -o $@ ${WN}

obj/%.o: src/%.cpp
	    $(CC) $(CFLAGS) $(INCL) -o $@ $<

.PHONY : clean
clean :
	    -rm $(EXE) && find obj/ -type f -delete
