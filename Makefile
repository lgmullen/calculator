# Makefile for EECS 280 Project 4

CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

all: test

test: List_compile_check.exe List_public_test.exe List_tests.exe Stack_public_test.exe calc.exe
	./List_compile_check.exe
	./List_public_test.exe
	./List_tests.exe

	./Stack_public_test.exe

	./calc.exe < calc_test00.in > calc_test00.out
	diff -q calc_test00.out calc_test00.out.correct

	./calc.exe < calc_test01.in > calc_test01.out
	diff -q calc_test01.out calc_test01.out.correct

calc.exe: calc.cpp List.h Stack.h
	$(CXX) $(CXXFLAGS) calc.cpp -o $@

List_tests.exe: List_tests.cpp List.h
	$(CXX) $(CXXFLAGS) $< -o $@

List_compile_check.exe: List_compile_check.cpp List.h
	$(CXX) $(CXXFLAGS) List_compile_check.cpp -o $@

List_public_test.exe: List_public_test.cpp List.h
	$(CXX) $(CXXFLAGS) $<  -o $@

Stack_public_test.exe: Stack_public_test.cpp List.h Stack.h
	$(CXX) $(CXXFLAGS) $< -o $@

Stack_tests.exe: Stack_tests.cpp List.h Stack.h
	$(CXX) $(CXXFLAGS) $< -o $@

# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean:
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out

# Run style check tools
CPPCHECK ?= cppcheck
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-0.13/bin/oclint
FILES := List.h List_tests.cpp Stack.h calc.cpp
style :
	$(CPPCHECK) \
    --language=c++ \
    --std=c++11 \
    --error-exitcode=1 \
    $(FILES)
	$(OCLINT) \
    -no-analytics \
    -rule=LongLine \
    -rule=HighNcssMethod \
    -rule=DeepNestedBlock \
    -rule=TooManyParameters \
    -rc=LONG_LINE=90 \
    -rc=NCSS_METHOD=40 \
    -rc=NESTED_BLOCK_DEPTH=4 \
    -rc=TOO_MANY_PARAMETERS=4 \
    -max-priority-1 0 \
    -max-priority-2 0 \
    -max-priority-3 0 \
    $(FILES) \
    -- -xc++ --std=c++11
	$(CPD) \
    --minimum-tokens 100 \
    --language cpp \
    --failOnViolation true \
    --files $(FILES)
	@echo "########################################"
	@echo "EECS 280 style checks PASS"
