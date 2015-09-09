OBJ=test_TileCoding.o TileCoding.o

CXXFLAG = -std=c++0x -I/opt/boost/boost_1_57_0 -g3
tile: $(OBJ)
	g++ -o $@ $^
%.o:%.cpp
	g++ -c $(CXXFLAG) $< 
clean:
	@rm -f tile *.o
