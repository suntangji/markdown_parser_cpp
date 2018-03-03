markdown_parser: main.o test.o
	g++ -g -std=c++11 main.o test.o -o markdown_parser
main.o:
	g++ -c main.cc -o main.o
test.o:parser.hpp
	g++ -c test.cc -o test.o

.PHONY:clean

clean:
	rm test.o main.o markdown_parser


