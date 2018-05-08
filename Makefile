CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
MEASURE=	src/measure

all:		inputs

inputs:	takesTwoInputs.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f inputs

test:		test-output test-memory test-time

test-output:	inputs
	@echo Testing output...
	@diff --suppress-common-lines -y <(./inputs < input1) output1
	@diff --suppress-common-lines -y <(./inputs < input2) output2
	@diff --suppress-common-lines -y <(./inputs < input3) output3


test-memory:	inputs
	@echo Testing memory...
	@[ `valgrind --leak-check=full ./inputs < input1 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
	@[ `valgrind --leak-check=full ./inputs < input2 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
	@[ `valgrind --leak-check=full ./inputs < input3 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]


test-time:	$(MEASURE) inputs
	@echo Testing time...
	@$(MEASURE) ./inputs < input1 | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
	@$(MEASURE) ./inputs < input2 | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
	@$(MEASURE) ./inputs < input3 | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
