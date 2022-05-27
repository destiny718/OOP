main: main.o graph.o node.o operation.o mymap.o 
	g++ -std=c++11 -o main main.o graph.o node.o operation.o mymap.o 
main.o: main.cpp graph.h
	g++ -c -std=c++11 -o main.o main.cpp 
graph.o: graph.cpp graph.h mymap.h node.h operation.h plus.h minus.h
	g++ -c -std=c++11 -o graph.o graph.cpp 
node.o: node.cpp node.h plus.h minus.h
	g++ -c -std=c++11 -o node.o node.cpp 
operation.o: operation.cpp operation.h node.h plus.h minus.h
	g++ -c -std=c++11 -o operation.o operation.cpp 
mymap.o: mymap.cpp mymap.h plus.h minus.h
	g++ -c -std=c++11 -o mymap.o mymap.cpp 
clean:
	del main *.o
