SRC = test_suite.cpp units.cpp
HDR = units.hpp
EXE = test.exe

FLAGS = -Wall -Werror -pedantic -std=c++11

FILES = $(SRC) $(HDR)

LINK = -L /usr/local/lib -l boost_unit_test_framework
DEF = -DBOOST_TEST_DYN_LINK

defaults: test
	./test

test: $(FILES)
	g++ $(FLAGS) $(SRC) -o $(EXE) $(DEF) $(LINK)

clean:
	rm -vf *.exe