bounding_box: main.o boxes.o pbmb_io.o 
	g++ -o bounding_box main.o boxes.o pbmb_io.o -lpthread

main.o: main.cc
	g++ -c -g main.cc -lpthread

boxes.o: boxes.h boxes.cc
	g++ -c -g boxes.cc

pbmb_io.o: pbmb_io.cpp pbmb_io.hpp
	g++ -c -g pbmb_io.cpp

clean: 
	rm *.o *~ 