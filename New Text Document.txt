bounding_box: main.o boxes.o 
	g++ -o bounding_box *.o 

main.o: main.cc
	g++ -c -g main.cc

boxes.o: boxes.h boxes.cc
	g++ -c boxes.cc

clean: 
	rm *.o *~ 