markdown_parser: main.o parser.o
	g++ -g -std=c++11 main.o parser.o -o markdown_parser
main.o:parser.h main.cc
	g++ -c main.cc -o main.o
parser.o:parser.h parser.cc
	g++ -c parser.cc -o parser.o

.PHONY:clean

clean:
	rm  main.o markdown_parser parser.o


