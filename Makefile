LIB = -lglut -lGLU

includes = API/*.h

TESTGL1 = testGl1.cpp API/*.cpp

testGl1: $(TESTGL1) $(includes)
	g++ $(TESTGL1) $(LIB) -o $@

%.o: %.cpp ${includes}
	g++ -Wall -Iinclude $(LIB) -c -o $@ $^

clean:
	rm ./run
	rm ./test3d