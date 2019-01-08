SRC = test_suite.cpp units.cpp
HDR = units.hpp
TEST_EXE = test.exe

CPP = g++
DEBUG = -g
RELEASE = -O3
CPP_FLAGS = -Wall -Werror -pedantic -std=c++17
DEBUG_FLAGS = $(CPP_FLAGS) $(DEBUG)
RELEASE_FLAGS = $(CPP_FLAGS) $(RELEASE)

LINK = -L /usr/local/lib -l boost_unit_test_framework
DEF = -DBOOST_TEST_DYN_LINK

FILES = $(SRC) $(HDR)

defaults: test
	./$(TEST_EXE)

test: $(FILES)
	$(CXX) $(DEBUG_FLAGS) $(SRC) -o $(TEST_EXE) $(DEF) $(LINK)

clean:
	rm -vf *.exe