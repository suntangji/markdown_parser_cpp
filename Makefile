markdown_parser: main.o parser.o
	g++ -g -std=c++11 main.o parser.o -o markdown_parser
main.o:parser.h main.cc
	g++ -c -std=c++11 main.cc -o main.o -g
parser.o:parser.h parser.cc
	g++ -c -std=c++11 parser.cc -o parser.o -g

.PHONY:clean

clean:
	rm  main.o markdown_parser parser.o


