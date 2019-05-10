test: testbst.o intbst.o
	g++ testbst.o intbst.o -o test
test2: test_intbst.o intbst.o
	g++ test_intbst.o intbst.o -o test2
intbst.o: intbst.h intbst.cpp
	g++ intbst.cpp -c
testbst.o: testbst.cpp
	g++ testbst.cpp -c
test_intbst.o: test_intbst.cpp
	g++ test_intbst.cpp -c
