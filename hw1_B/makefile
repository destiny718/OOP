all:main.o product.o sum.o
	g++ $^ -o main

main.o: main.cpp functions.h
	g++ -c $< -o main.o

product.o:product.cpp functions.h
	g++ -c $< -o product.o

sum.o:sum.cpp functions.h
	g++ -c $< -o sum.o

clean:
	rm *.o main

debug:main.cpp product.cpp sum.cpp functions.h
	g++ -c -DDEBUG main.cpp -o main.o
	g++ -c -DDEBUG product.cpp -o product.o
	g++ -c -DDEBUG sum.cpp -o sum.o
	g++ -DDEBUG main.o product.o sum.o -o main