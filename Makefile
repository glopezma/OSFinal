bounding_box: main.o boxes.o pbmb_io.o 
	g++ -o bounding_box *.o 

main.o: main.cc
	g++ -c -g main.cc

boxes.o: boxes.h boxes.cc
	g++ -c -g boxes.cc

pbmb_io.o: pbmb_io.cpp pbmb_io.hpp
	g++ -c pbmb_io.cpp

clean: 
	rm *.o *~ 