all:main.o Server.o
	g++ $^ -o main

main.o:main.cpp Server.h Task.h
	g++ -c $< -o main.o

Server.o:Server.cpp Server.h Task.h	
	g++ -c $< -o Server.o

clean:
	rm main *.o