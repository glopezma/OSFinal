bounding_box: pbmb_io.o main.o 
	g++ -o bounding_box *.o 

main.o: pbmb_io_prb.cpp
	g++ -c -g pbmb_io_prb.cpp

pbmb_io.o: pbmb_io.cpp pbmb_io.hpp
	g++ -c pbmb_io.cpp

clean: 
	rm *.o *~ 